#include <QFileDialog>
#include <QStringListModel>
#include <QSqlError>
#include <QDomDocument>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "changedatabasedialog.h"

#include "wellformdata.h"
#include "productionformdata.h"
#include "reservoirformdata.h"
#include "mineralogyformdata.h"
#include "laboratoryformdata.h"

#include "programformdata.h"
#include "treatmentformdata.h"
#include "maintreatmentformdata.h"
#include "picklingformdata.h"
#include "preflushformdata.h"
#include "overflushformdata.h"
#include "stfbformdata.h"

#include "calculationformdata.h"

#include "singleselectionparameter.h"
#include "multiselectionparameter.h"
#include "multiselectionparameterwithcategory.h"
#include "mapselectionparameter.h"

#include "rangeparameterrecommendation.h"
#include "comparisonparameterrecommendation.h"
#include "rangeparameterrecommendationwithcategory.h"

#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    translator = 0;

    ui->setupUi(this);

    QActionGroup* languageGroup = new QActionGroup(this);

    languageGroup->setExclusive(true);

    languageGroup->addAction(ui->actionKazakh);
    languageGroup->addAction(ui->actionRussian);
    languageGroup->addAction(ui->actionEnglish);

    connect(languageGroup, SIGNAL(triggered(QAction*)), this, SLOT(languageChanged(QAction*)));


    currentForm = 0;
    currentFormData = 0;

    ui->treeWidget->hideColumn(1);

    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    bool opened = Settings::get()->db().open();

    displayStatus(opened);

    recommendationFromListModel = new QSqlQueryModel(this);

    ui->recommendationFromComboBox->setModel(recommendationFromListModel);


    initializeFormMap();

    initializeParameterMap();

    initializeRecommendationId();

    loadCategoryMap();

    loadFieldMap();        

    displayFormList();

    displayRecommendationFromList();
}

MainWindow::~MainWindow()
{
    delete ui;

    qDeleteAll(formMap);

    formMap.clear();

    qDeleteAll(parameterMap);

    parameterMap.clear();

    Settings::releaseSettings();
}

void MainWindow::setBoxTitle(QString boxTitle)
{
    ui->groupBox->setTitle(boxTitle);
}

void MainWindow::treeWidgetItemClicked(QTreeWidgetItem *item, int column)
{
    int id = item->data(1, Qt::DisplayRole).toInt();

    qDebug() << "MainWindow::treeWidgetItemClicked index = " << id;

    currentId = id;

    displayForm(id);
}

void MainWindow::saveData()
{
    qDebug() << "MainWindow::saveData()";

    if(currentFormData != 0)
    {
        currentFormData->saveFormData(formData);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save data"), QString(), tr("Data (*.xml);; All files (*.*)"));

    QDomDocument document;

    QDomElement dataElement = document.createElement("data");

    dataElement.setAttribute("language", Settings::get()->locale());
    dataElement.setAttribute("recommendationId", recommendationId);

    for(int i = 0; i < formData.keys().count(); i++)
    {
        QString key = formData.keys().at(i);

        QVariant value = formData.values().at(i);

        if(!value.isNull() && (QString(value.typeName()) != QString("QString") || !value.toString().isEmpty()))
        {
            QDomElement propertyElement = document.createElement("property");

            propertyElement.setAttribute("key", key);
//          propertyElement.setAttribute("type", value.typeName());

            if(fieldMap.contains(key)) propertyElement.setAttribute("name", fieldMap[key]);

            if(parameterMap.contains(key))
            {
                parameterMap[key]->addParameterElement(recommendationId, value, propertyElement, document, formData);
            }
            else
            {
                QDomElement parameterElement = document.createElement("parameter");

                parameterElement.setAttribute("value", value.toString());

                propertyElement.appendChild(parameterElement);
            }

            dataElement.appendChild(propertyElement);
        }
    }

    document.appendChild(dataElement);


    QDomNode xmlNode = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");

    document.insertBefore(xmlNode, document.firstChild());

    QFile file(fileName);

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    document.save(out, 3);

    file.close();
}

void MainWindow::openData()
{
    qDebug() << "MainWindow::openData()";

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open data"), QString(), tr("Data (*.xml);; All files (*.*)"));

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QDomDocument document;

    if(!document.setContent(&file))
    {
        file.close();
        return;
    }

    file.close();

    QDomElement dataElement = document.documentElement();

    if(!dataElement.isNull())
    {
        QDomNodeList childs = dataElement.childNodes();

        int count = childs.count();

        for(int i = 0; i < count; i++)
        {
            QDomNode node = childs.at(i);

            if(!node.isNull() && node.isElement())
            {
                QDomElement element = node.toElement();

                QString key = element.attribute("key");

                if(!key.isEmpty())
                {
                    if(parameterMap.contains(key)) parameterMap[key]->loadDataFromElement(key, element, document, formData);
                    else
                    {
                        QDomElement childElement = element.firstChildElement();

                        if(!childElement.isNull())
                        {
                            QString value = childElement.attribute("value");

                            if(!value.isEmpty()) formData[key] = value;
                        }
                    }
                }
            }
        }
    }

    if(currentFormData != 0) currentFormData->display(fieldMap, formData);
}

void MainWindow::recommendationFromIndexChanged(int index)
{
    if(index >= 0)
    {
        Settings::get()->setRecommendationIndex(index);

        qDebug() << "recommendationFromIndexChanged: " << Settings::get()->recommendationIndex();

        initializeRecommendationId();
    }
}

void MainWindow::openChangeDatabaseDialog()
{
    ChangeDatabaseDialog *changeDatabaseDialog = new ChangeDatabaseDialog(this);

    changeDatabaseDialog->setAttribute(Qt::WA_DeleteOnClose);

    changeDatabaseDialog->exec();

    loadCategoryMap();

    loadFieldMap();

    displayFormList();

    displayRecommendationFromList();

    initializeRecommendationId();
}

void MainWindow::languageChanged(QAction *action)
{
    QString language = action->objectName().remove("action").toLower();

    qDebug() << "MainWindow::languageChanged: " << language;

    Settings::get()->setLocale(language);

    if(translator != 0)
    {
        qApp->removeTranslator(translator);

        delete translator;

        translator = 0;
    }

    translator = new QTranslator();

    translator->load(QString("translations/aaa_input_%1").arg(language));

    qApp->installTranslator(translator);

    ui->retranslateUi(this);

    statusBar()->showMessage(tr("Language change to: %1, %2").arg(Settings::get()->locale()).arg(Settings::get()->shortLocale()));

    loadCategoryMap();

    loadFieldMap();

    displayFormList();

    displayRecommendationFromList();

    initializeRecommendationId();
}

void MainWindow::initializeFormMap()
{
    formMap[1] = new FormData("Data entry of the candidate well");

    formMap[2] = new FormData("Data entry of the proposed acidizing program");

    formMap[3] = new CalculationFormData("Calculation data", 0);

    formMap[5] = new WellFormData("Well Data", 0);

    formMap[6] = new ReservoirFormData("Reservoir Data", 0);

    formMap[7] = new ProductionFormData("Production Data", 0);

    formMap[8] = new MineralogyFormData("Mineralogy Data", 0);

    formMap[9] = new LaboratoryFormData("Lab data and rig operation", 0);

    formMap[11] = new ProgramFormData("Program procedures", 0);

    formMap[12] = new TreatmentFormData("Treatment design", 0);

    formMap[13] = new MainTreatmentFormData("Main treatment additives", 0);

    formMap[14] = new PicklingFormData("Pickling additives", 0);

    formMap[15] = new PreFlushFormData("Pre-flush additives", 0);

    formMap[16] = new OverFlushFormData("Over-flush additives", 0);

    formMap[17] = new STFBFormData("Soaking time and flow back", 0);
}

void MainWindow::initializeParameterMap()
{
    QString criteriaQueryStr = "";

    QString queryStr = "select name_en from well_type where id=?";

    QString recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='wd_well_type' and parameter_id=? and recommendation_id=?";

    parameterMap["wd_well_type"] = new SingleSelectionParameter(queryStr, new ParameterRecommendation(recommendationQueryStr));


    criteriaQueryStr = "select td.id, td.field_key, td.criteria from total_depth td, recommendation_guide rg where rg.parameter_id=td.id and rg.field_key='wd_total_depth' and rg.recommendation_id=?";

    recommendationQueryStr = "select rg.id, rg.parameter_id, td.field_key, td.criteria, rg.recommendation_en from recommendation_guide rg, total_depth td where td.id=rg.parameter_id and rg.field_key='wd_total_depth' and rg.parameter_id in (%1) and rg.recommendation_id=%2";

    parameterMap["wd_total_depth"] = new InputParameter(new ComparisonParameterRecommendation("wd_total_depth", criteriaQueryStr, recommendationQueryStr));


    recommendationQueryStr = "select rg.id, rg.parameter_id, pzl.min, pzl.max, rg.recommendation_en from recommendation_guide rg, paz_zone_length pzl where (pzl.min is null or pzl.min < ?) and (pzl.max is null or pzl.max > ?) and rg.parameter_id=pzl.id and rg.field_key='wd_paz_zone_length' and rg.recommendation_id=?";

    parameterMap["wd_paz_zone_length"] = new InputParameter(new RangeParameterRecommendation(recommendationQueryStr));


    criteriaQueryStr = "select mid.id, mid.field_key, mid.criteria from minimum_inside_diameter mid, recommendation_guide rg where rg.parameter_id=mid.id and rg.field_key='wd_min_inside_diameter' and rg.recommendation_id=?";

    recommendationQueryStr = "select rg.id, rg.parameter_id, mid.field_key, mid.criteria, rg.recommendation_en from recommendation_guide rg, minimum_inside_diameter mid where mid.id=rg.parameter_id and rg.field_key='wd_min_inside_diameter' and rg.parameter_id in (%1) and rg.recommendation_id=%2";

    parameterMap["wd_min_inside_diameter"] = new InputParameter(new ComparisonParameterRecommendation("wd_min_inside_diameter", criteriaQueryStr, recommendationQueryStr));


    queryStr = "select name_en from completion_type where id=?";

    recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='wd_completion_type' and parameter_id=? and recommendation_id=?";

    parameterMap["wd_completion_type"] = new SingleSelectionParameter(queryStr, new ParameterRecommendation(recommendationQueryStr));


    recommendationQueryStr = "select rg.id, rg.parameter_id, rt.min, rt.max, rg.recommendation_en from recommendation_guide rg, reservoir_temperature rt where (rt.min is null or rt.min < ?) and (rt.max is null or rt.max > ?) and rg.parameter_id=rt.id and rg.field_key='rd_reservoir_temperature' and rg.recommendation_id=?";

    parameterMap["rd_reservoir_temperature"] = new InputParameter(new RangeParameterRecommendation(recommendationQueryStr));


    criteriaQueryStr = "select rp.id, rp.field_key, rp.criteria from reservoir_pressure rp, recommendation_guide rg where rg.parameter_id=rp.id and rg.field_key='rd_reservoir_pressure' and rg.recommendation_id=?";

    recommendationQueryStr = "select rg.id, rg.parameter_id, rp.field_key, rp.criteria, rg.recommendation_en from recommendation_guide rg, reservoir_pressure rp where rp.id=rg.parameter_id and rg.field_key='rd_reservoir_pressure' and rg.parameter_id in (%1) and rg.recommendation_id=%2";

    parameterMap["rd_reservoir_pressure"] = new InputParameter(new ComparisonParameterRecommendation("rd_reservoir_pressure", criteriaQueryStr, recommendationQueryStr));


    criteriaQueryStr = "select pp.id, pp.field_key, pp.criteria from pumping_pressure pp, recommendation_guide rg where rg.parameter_id=pp.id and rg.field_key='rd_pumping_pressure' and rg.recommendation_id=?";

    recommendationQueryStr = "select rg.id, rg.parameter_id, pp.field_key, pp.criteria, rg.recommendation_en from recommendation_guide rg, pumping_pressure pp where pp.id=rg.parameter_id and rg.field_key='rd_pumping_pressure' and rg.parameter_id in (%1) and rg.recommendation_id=%2";

    parameterMap["rd_pumping_pressure"] = new InputParameter(new ComparisonParameterRecommendation("rd_pumping_pressure", criteriaQueryStr, recommendationQueryStr));


    queryStr = "select id, name_en from reservoir_permeability where id in (%1)";

    recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='rd_permeability_type' and parameter_id=? and recommendation_id=?";

    parameterMap["rd_permeability_type"] = new MultiSelectionParameter(queryStr, new ParameterRecommendation(recommendationQueryStr));


    queryStr = "select id, name_en from drive_mechanism where id in (%1)";

    recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='rd_drive_mechanism' and parameter_id=? and recommendation_id=?";

    parameterMap["rd_drive_mechanism"] = new MultiSelectionParameter(queryStr, new ParameterRecommendation(recommendationQueryStr));


    recommendationQueryStr = "select rg.id, rg.parameter_id, wc.min, wc.max, rg.recommendation_en from recommendation_guide rg, water_cut wc where (wc.min is null or wc.min < ?) and (wc.max is null or wc.max > ?) and rg.parameter_id=wc.id and rg.field_key='pd_water_cut' and rg.recommendation_id=?";

    parameterMap["pd_water_cut"] = new InputParameter(new RangeParameterRecommendation(recommendationQueryStr));


    recommendationQueryStr = "select rg.id, rg.parameter_id, h.min, h.max, rg.recommendation_en from recommendation_guide rg, h2s h where (h.min is null or h.min < ?) and (h.max is null or h.max > ?) and rg.parameter_id=h.id and rg.field_key='pd_h2s' and rg.recommendation_id=?";

    parameterMap["pd_h2s"] = new InputParameter(new RangeParameterRecommendation(recommendationQueryStr));


    queryStr = "select fd.id, fd.name_en, fd.type_id, fdt.name_en from formation_damage fd, formation_damage_type fdt where fdt.id=fd.type_id and fd.id in (%1)";

    recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='pd_formation_damage' and parameter_id=? and recommendation_id=?";

    parameterMap["pd_formation_damage"] = new MultiSelectionParameterWithCategory(queryStr, new ParameterRecommendation(recommendationQueryStr));


    recommendationQueryStr = "select rg.id, rg.parameter_id, dr.min, dr.max, rg.recommendation_en from recommendation_guide rg, damage_radius dr where (dr.min is null or dr.min < ?) and (dr.max is null or dr.max > ?) and rg.parameter_id=dr.id and rg.field_key='pd_damage_radius' and rg.recommendation_id=?";

    parameterMap["pd_damage_radius"] = new InputParameter(new RangeParameterRecommendation(recommendationQueryStr));


    queryStr = "select name_en from formation_types where id=?";

    recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='md_formation_types' and parameter_id=? and recommendation_id=?";

    parameterMap["md_formation_types"] = new SingleSelectionParameter(queryStr, new ParameterRecommendation(recommendationQueryStr));


    queryStr = "select name_en from clays_types where id=?";

    recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='md_clays_types' and parameter_id=? and recommendation_id=?";

    parameterMap["md_clays_types"] = new SingleSelectionParameter(queryStr, new ParameterRecommendation(recommendationQueryStr));


    queryStr = "select id, name_en from compatibility_data where id in (%1)";

    recommendationQueryStr = "select id, parameter_id, recommendation_en from recommendation_guide where field_key='ld_compatibility_data' and parameter_id=? and recommendation_id=?";

    parameterMap["ld_compatibility_data"] = new MultiSelectionParameter(queryStr, new ParameterRecommendation(recommendationQueryStr));


    queryStr = "select id, name_en from acid_type where id in (%1)";

    recommendationQueryStr = "select rg.id, rg.parameter_id, aa.min, aa.max, rg.recommendation_en from recommendation_guide rg, acid_additives aa where ?=? and aa.acid_type_id=? and rg.parameter_id=aa.id and rg.field_key='aa_additives_range' and rg.recommendation_id=?";

    parameterMap["mta_additives"] = new MapSelectionParameter(queryStr, new RangeParameterRecommendationWithCategory("mta_additives", recommendationQueryStr));


    queryStr = "select id, name_en from acid_type where id in (%1)";

    recommendationQueryStr = "select rg.id, rg.parameter_id, aa.min, aa.max, rg.recommendation_en from recommendation_guide rg, acid_additives aa where ?=? and aa.acid_type_id=? and rg.parameter_id=aa.id and rg.field_key='aa_additives_range' and rg.recommendation_id=?";

    parameterMap["pa_additives"] = new MapSelectionParameter(queryStr, new RangeParameterRecommendationWithCategory("pa_additives", recommendationQueryStr));
}

void MainWindow::initializeRecommendationId()
{
    QModelIndex index = recommendationFromListModel->index(Settings::get()->recommendationIndex(), 0);

    if(index.isValid()) recommendationId = index.data().toInt();
}

void MainWindow::loadCategoryMap()
{
    categoryMap[1] = "Data entry of the candidate well - translate";

    categoryMap[2] = "Data entry of the proposed acidizing program - translate";

    categoryMap[3] = "Calculation data - translate";

    categoryMap[5] = "Well Data - translate";

    categoryMap[6] = "Reservoir Data - translate";

    categoryMap[7] = "Production Data - translate";

    categoryMap[8] = "Mineralogy Data - translate";

    categoryMap[9] = "Lab data and rig operation - translate";

    categoryMap[11] = "Program procedures - translate";

    categoryMap[12] = "Treatment design - translate";

    categoryMap[13] = "Main treatment additives - translate";

    categoryMap[14] = "Pickling additives - translate";

    categoryMap[15] = "Pre-flush additives - translate";

    categoryMap[16] = "Over-flush additives - translate";

    categoryMap[17] = "Soaking time and flow back - translate";
}

void MainWindow::loadFieldMap()
{
    fieldMap["wd_well_type"] = "Тип скважины";
}

void MainWindow::displayFormList()
{
    int childCount = ui->treeWidget->topLevelItemCount();

    for(int i = 0; i < childCount; i++)
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);

        displayFormListItem(item);
    }

    if(childCount > 0)
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(0);

        item->setSelected(true);

        currentId = item->data(1, Qt::DisplayRole).toInt();

        displayForm(currentId);
    }
}

void MainWindow::displayFormListItem(QTreeWidgetItem *item)
{
    item->setExpanded(true);

    int childCount = item->childCount();

    int id = item->data(1, Qt::DisplayRole).toInt();

    if(categoryMap.contains(id))
    {
        QString title = categoryMap[id];;

        item->setText(0, title);
        item->setToolTip(0, title);

        if(formMap.contains(id))
        {
            FormData* formData = formMap[id];

            formData->setTitle(title);

            if(childCount > 0)
            {
                int cid = item->child(0)->data(1, Qt::DisplayRole).toInt();

                formData->setFirstChildId(cid);
            }
        }
    }

    for(int i = 0; i < childCount; i++)
    {
        displayFormListItem(item->child(i));
    }
}

void MainWindow::displayForm(int id)
{
    if(currentFormData != 0)
    {
        currentFormData->saveFormData(formData);

        if(currentForm != 0)
        {
            ui->groupBox->layout()->removeWidget(currentForm);

            currentForm->setParent(0);

            currentForm = 0;
        }

        currentFormData = 0;
    }

    if(formMap.contains(id))
    {
        QMap<QString, QString> formDataMap;

        currentFormData = formMap[id];

        ui->groupBox->setTitle(currentFormData->title());

        currentForm = currentFormData->display(formDataMap, formData);

        if(currentForm != 0)
        {
            currentForm->setParent(ui->groupBox);

            ui->groupBox->layout()->addWidget(currentForm);
        }
        else
        {
            int firstChildId = currentFormData->firstChildId();

            if(firstChildId >= 0) displayForm(firstChildId);
        }
    }
}

void MainWindow::displayRecommendationFromList()
{
    recommendationFromListModel->setQuery(QString("select id, name_%1 from recommendation").arg(Settings::get()->shortLocale()));

    ui->recommendationFromComboBox->setModelColumn(1);

    ui->recommendationFromComboBox->setCurrentIndex(Settings::get()->recommendationIndex());

    qDebug() << "MainWindow::displayRecommendationFromList, current index: " << ui->recommendationFromComboBox->currentIndex();
}

void MainWindow::displayStatus(bool opened)
{
    if(opened)
    {
        statusBar()->showMessage(QString("Database connection opened, path = %1").arg(Settings::get()->dbPath()), 5000);
    }
    else
    {
        statusBar()->showMessage(QString("Database connection error, path = %1, error: %2").arg(Settings::get()->dbPath()).arg(Settings::get()->db().lastError().text()), 5000);
    }
}
