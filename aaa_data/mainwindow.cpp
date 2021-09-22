#include <QMessageBox>
#include <QActionGroup>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "changedatabasedialog.h"
#include "parameterdatadialog.h"
#include "parameterdatawithcategorydialog.h"
#include "createparametervaluedialog.h"
#include "editparametervaluedialog.h"

#include "recommendationmodel.h"

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

    bool opened = Settings::get()->db().open();

    displayStatus(opened);

    recommendationQueryModel = new QSqlQueryModel(this);
    recommendationModel = new RecommendationModel(this);
    recommendationFromListModel = new QSqlQueryModel(this);

    recommendationModel->setSourceModel(recommendationQueryModel);

    ui->recommendationComboBox->setModel(recommendationFromListModel);
    ui->recommendationTableView->setModel(recommendationModel);

    tableViewContextMenu = new QMenu(this);

    tableViewContextMenu->addAction(ui->actionCreate);
    tableViewContextMenu->addAction(ui->actionEdit);
    tableViewContextMenu->addAction(ui->actionDelete);

    connect(tableViewContextMenu, SIGNAL(triggered(QAction*)), this, SLOT(contextMenuTriggered(QAction*)));

    displayRecommendationFromList();
}

MainWindow::~MainWindow()
{
    delete ui;

    Settings::free();
}

void MainWindow::openAboutDialog()
{
    AboutDialog *aboutDialog = new AboutDialog(this);

    aboutDialog->setAttribute(Qt::WA_DeleteOnClose);

    aboutDialog->show();
}

void MainWindow::openChangeDatabaseDialog()
{
    ChangeDatabaseDialog *changeDatabaseDialog = new ChangeDatabaseDialog(this);

    changeDatabaseDialog->setAttribute(Qt::WA_DeleteOnClose);

    changeDatabaseDialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openEditRecommendationsDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from recommendation").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from recommendation where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into recommendation(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update recommendation set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from recommendation where id=?";

    QString boxCreateTitle = tr("Create Recommendation From");
    QString boxUpdateTitle = tr("Edit Recommendation From (ID = %1)");
    QString boxDeleteTitle = tr("Delete Recommendation From");

    QString boxDeleteQuestion = tr("Delete Recommendation From with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Recommendation From"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openWellTypeDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from well_type").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from well_type where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into well_type(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update well_type set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from well_type where id=?";

    QString boxCreateTitle = tr("Create Well Type");
    QString boxUpdateTitle = tr("Edit Well Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Well Type");

    QString boxDeleteQuestion = tr("Delete Well Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Well Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openCompletionTypeDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from completion_type").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from completion_type where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into completion_type(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update completion_type set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from completion_type where id=?";

    QString boxCreateTitle = tr("Create Completion Type");
    QString boxUpdateTitle = tr("Edit Completion Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Completion Type");

    QString boxDeleteQuestion = tr("Delete Completion Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Completion Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openDeviationDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from deviation").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from deviation where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into deviation(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update deviation set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from deviation where id=?";

    QString boxCreateTitle = tr("Create Deviation Type");
    QString boxUpdateTitle = tr("Edit Deviation Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Deviation Type");

    QString boxDeleteQuestion = tr("Delete Deviation Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Deviation Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openHoleTypeDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from hole_type").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from hole_type where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into hole_type(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update hole_type set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from hole_type where id=?";

    QString boxCreateTitle = tr("Create Hole Type");
    QString boxUpdateTitle = tr("Edit Hole Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Hole Type");

    QString boxDeleteQuestion = tr("Delete Hole Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Hole Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openReservoirTypeDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from reservoir_permeability").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from reservoir_permeability where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into reservoir_permeability(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update reservoir_permeability set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from reservoir_permeability where id=?";

    QString boxCreateTitle = tr("Create Reservoir Type");
    QString boxUpdateTitle = tr("Edit Reservoir Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Reservoir Type");

    QString boxDeleteQuestion = tr("Delete Reservoir Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Reservoir Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openDriveMechanismDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from drive_mechanism").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from drive_mechanism where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into drive_mechanism(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update drive_mechanism set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from drive_mechanism where id=?";

    QString boxCreateTitle = tr("Create Drive Mechanism");
    QString boxUpdateTitle = tr("Edit Drive Mechanism (ID = %1)");
    QString boxDeleteTitle = tr("Delete Drive Mechanism");

    QString boxDeleteQuestion = tr("Delete Drive Mechanism with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Drive Mechanism"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openCompatibilityDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from compatibility_data").arg(Settings::get()->shortLocale());
    QString selectQueryStr =QString( "select name_%1, description_%1 from compatibility_data where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into compatibility_data(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update compatibility_data set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from compatibility_data where id=?";

    QString boxCreateTitle = tr("Create Compatibility Data");
    QString boxUpdateTitle = tr("Edit Compatibility Data (ID = %1)");
    QString boxDeleteTitle = tr("Delete Compatibility Data");

    QString boxDeleteQuestion = tr("Delete Compatibility Data with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Compatibility Data"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openFormationTypeDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from formation_types").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from formation_types where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into formation_types(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update formation_types set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from formation_types where id=?";

    QString boxCreateTitle = tr("Create Formation Type");
    QString boxUpdateTitle = tr("Edit Formation Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Formation Type");

    QString boxDeleteQuestion = tr("Delete Formation Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Formation Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openClaysTypesDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from clays_types").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from clays_types where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into clays_types(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update clays_types set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from clays_types where id=?";

    QString boxCreateTitle = tr("Create Clay Type");
    QString boxUpdateTitle = tr("Edit Clay Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Clay Type");

    QString boxDeleteQuestion = tr("Delete Clay Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Clay Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openFormationDamageTypeDataDialog()
{
    QString queryStr = QString("select id, name_%1, description_%1 from formation_damage_type").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from formation_damage_type where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into formation_damage_type(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update formation_damage_type set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from formation_damage_type where id=?";

    QString boxCreateTitle = tr("Create Formation Damage Type");
    QString boxUpdateTitle = tr("Edit Formation Damage Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Formation Damage Type");

    QString boxDeleteQuestion = tr("Delete Formation Damage Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Formation Damage Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openFormationDamageDataDialog()
{
    QString queryStr = QString("select fd.id, fd.type_id, fdt.name_%1, fd.name_%1, fd.description_%1 from formation_damage fd, formation_damage_type fdt where fdt.id = fd.type_id order by fd.type_id").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from formation_damage where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into formation_damage(type_id, name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update formation_damage set type_id=?, name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from formation_damage where id=?";
    QString categoryQueryStr = QString("select id, name_%1 from formation_damage_type").arg(Settings::get()->shortLocale());

    QString boxCreateTitle = tr("Create Formation Damage");
    QString boxUpdateTitle = tr("Edit Formation Damage (ID = %1)");
    QString boxDeleteTitle = tr("Delete Formation Damage");

    QString boxDeleteQuestion = tr("Delete Formation Damage with ID = %1");

    QString categoryHeaderData = tr("Type");
    QString nameHeaderData = tr("Name");
    QString descriptionHeaderData = tr("Description");

    ParameterDataWithCategoryDialog *dialog = new ParameterDataWithCategoryDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr, categoryQueryStr,
                                                            boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion,
                                                            categoryHeaderData, nameHeaderData, descriptionHeaderData, this);

    dialog->setWindowTitle(tr("Formation Damage"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openAcidAdditivesType()
{
    QString queryStr = QString("select id, name_%1, description_%1 from acid_type").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from acid_type where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = "insert into acid_type(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update acid_type set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = "delete from acid_type where id=?";

    QString boxCreateTitle = tr("Create Acid Additives Type");
    QString boxUpdateTitle = tr("Edit Acid Additives Type (ID = %1)");
    QString boxDeleteTitle = tr("Delete Acid Additives Type");

    QString boxDeleteQuestion = tr("Delete Acid Additives Type with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Acid Additives Type"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openRecommendationFieldCategory()
{
    QString queryStr = QString("select id, name_%1, description_%1 from recommendation_field_category").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from recommendation_field_category where id=?").arg(Settings::get()->shortLocale());
    QString createQueryStr = ""; // "insert into recommendation_field_category(name_kz, description_kz, name_ru, description_ru, name_en, description_en) values (?, ?, ?, ?, ?, ?)";
    QString updateQueryStr = QString("update recommendation_field_category set name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString deleteQueryStr = ""; // "delete from recommendation_field_category where id=?";

    QString boxCreateTitle = ""; // tr("Create Recommendation Field Category");
    QString boxUpdateTitle = tr("Edit Recommendation Field Category (ID = %1)");
    QString boxDeleteTitle = ""; // tr("Delete Recommendation Field Category");

    QString boxDeleteQuestion = ""; // tr("Delete Recommendation Field Category with ID = %1");

    ParameterDataDialog *dialog = new ParameterDataDialog(queryStr, selectQueryStr, createQueryStr, updateQueryStr, deleteQueryStr,
                                                          boxCreateTitle, boxUpdateTitle, boxDeleteTitle, boxDeleteQuestion, this);

    dialog->setWindowTitle(tr("Recommendation Field Category"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::openRecommendationField()
{
    QString queryStr = QString("select rf.id, rf.category_id, rfc.name_%1, rf.name_%1, rf.description_%1 from recommendation_field rf, recommendation_field_category rfc where rfc.id = rf.category_id order by rf.category_id").arg(Settings::get()->shortLocale());
    QString selectQueryStr = QString("select name_%1, description_%1 from recommendation_field where id=?").arg(Settings::get()->shortLocale());
    QString updateQueryStr = QString("update recommendation_field set category_id=?, name_%1=?, description_%1=? where id=?").arg(Settings::get()->shortLocale());
    QString categoryQueryStr = QString("select id, name_%1 from recommendation_field_category").arg(Settings::get()->shortLocale());

    QString boxUpdateTitle = tr("Edit Recommendation Field (ID = %1)");

    QString categoryHeaderData = tr("Category");
    QString nameHeaderData = tr("Field");
    QString descriptionHeaderData = tr("Description");

    ParameterDataWithCategoryDialog *dialog = new ParameterDataWithCategoryDialog(queryStr, selectQueryStr, "", updateQueryStr, "", categoryQueryStr,
                                                            "", boxUpdateTitle, "", "",
                                                            categoryHeaderData, nameHeaderData, descriptionHeaderData, this);

    dialog->setWindowTitle(tr("Recommendation Field"));

    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

    displayRecommendationFromList();
}

void MainWindow::languageChanged(QAction *action)
{
    QString language = action->objectName().remove("action").toLower();

    Settings::get()->setLocale(language);

    if(translator != 0)
    {
        qApp->removeTranslator(translator);

        delete translator;

        translator = 0;
    }

    translator = new QTranslator();

    translator->load(QString("translations/aaa_data_%1").arg(language));

    qApp->installTranslator(translator);

    ui->retranslateUi(this);

    statusBar()->showMessage(tr("Language change to: %1, %2").arg(Settings::get()->locale()).arg(Settings::get()->shortLocale()));

    displayRecommendationFromList();
}

void MainWindow::recommendationComboBoxIndexChanged(int index)
{
    qDebug() << "MainWindow recommendationComboBoxIndexChanged: " << index;

    int recommendationId = -1;

    if(index >= 0)
    {
        Settings::get()->setRecommendationIndex(index);

        QModelIndex idIndex = recommendationFromListModel->index(index, 0);

        if(idIndex.isValid()) recommendationId = recommendationFromListModel->data(idIndex).toInt();
    }

    displayRecommendations(recommendationId);
}

void MainWindow::contextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->recommendationTableView->indexAt(pos);

    int row = index.row();
    int column = index.column();

    ui->actionEdit->setEnabled(index.isValid() && (column == 6 || column == 7));
    ui->actionDelete->setEnabled(index.isValid() && (column == 6 || column == 7));

    currentIndex = index;

    tableViewContextMenu->popup(ui->recommendationTableView->viewport()->mapToGlobal(pos));

    qDebug() << QString("Table view context menu: row=%0, column=%1").arg(index.row()).arg(index.column());
}

void MainWindow::contextMenuTriggered(QAction *action)
{
    qDebug() << QString("Table view context menu action triggered: action=%0, row=%1, column=%2").arg(action->objectName()).arg(currentIndex.row()).arg(currentIndex.column());

    int recommendationFromId = -1;
    int dataId = -1;
    int categoryId = -1;
    int propertyId = -1;
    int parameterId = -1;

    QString fieldKey;
    QString propertyText;
    QString categoryText;
    QString recommendation;

    QModelIndex recommendationIndex = recommendationFromListModel->index(Settings::get()->recommendationIndex(), 0);

    if(recommendationIndex.isValid()) recommendationFromId = recommendationIndex.data().toInt();

    if(currentIndex.isValid())
    {
        dataId = recommendationQueryModel->index(currentIndex.row(), 0).data().toInt();

        categoryId = recommendationQueryModel->index(currentIndex.row(), 3).data().toInt();

        propertyId = recommendationQueryModel->index(currentIndex.row(), 1).data().toInt();

        parameterId = recommendationQueryModel->index(currentIndex.row(), 6).data().toInt();

        fieldKey = recommendationQueryModel->index(currentIndex.row(), 2).data().toString();

        propertyText = recommendationQueryModel->index(currentIndex.row(), 5).data().toString();

        categoryText = recommendationQueryModel->index(currentIndex.row(), 4).data().toString();

        recommendation = recommendationQueryModel->index(currentIndex.row(), 7).data().toString();
    }    

    if(action->objectName() == QString("actionCreate"))
    {
        CreateParameterValueDialog* dialog = new CreateParameterValueDialog(recommendationFromId, propertyId, categoryId, parameterId, fieldKey, this);

        dialog->setAttribute(Qt::WA_DeleteOnClose);

        dialog->exec();

        displayRecommendationFromList();
    }
    else if(action->objectName() == QString("actionEdit"))
    {
        EditParameterValueDialog* dialog = new EditParameterValueDialog(dataId, parameterId, fieldKey, recommendation, propertyText, categoryText, this);

        dialog->setAttribute(Qt::WA_DeleteOnClose);

        dialog->exec();

        displayRecommendationFromList();
    }
    else if(action->objectName() == QString("actionDelete"))
    {
        QString question = tr("Delete Recommendation with ID = %1?").arg(dataId);

        int answer = QMessageBox::question(this, tr("Delete Recommendation"), question, QMessageBox::Yes | QMessageBox::No);

        if(answer == QMessageBox::Yes)
        {
            QSqlQuery query;

            query.prepare("delete from recommendation_guide where id=?");
            query.addBindValue(dataId);

            bool queryExecuted = query.exec();

            qDebug() << "Query executed: " << queryExecuted;

            if(!queryExecuted)
            {
                qDebug() << "Query execution error: " << query.lastError();
            }

            displayRecommendationFromList();
        }
    }
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

void MainWindow::displayRecommendationFromList()
{
    recommendationFromListModel->setQuery(QString("select id, name_%1 from recommendation").arg(Settings::get()->shortLocale()));

    ui->recommendationComboBox->setModelColumn(1);

    ui->recommendationComboBox->setCurrentIndex(Settings::get()->recommendationIndex());
}

void MainWindow::displayRecommendations(int id)
{
    QString queryStr = QString("select g.id, f.id as field_id, g.field_key, c.id as category_id, c.name_%1 as category, f.name_%1 as field, parameter_id, recommendation_%1 as recommendation ").arg(Settings::get()->shortLocale());

    queryStr += "from recommendation_guide g, recommendation_field f, recommendation_field_category c ";

    queryStr += "where c.id = f.category_id ";

    queryStr += "and f.key = g.field_key ";

    queryStr += "and g.recommendation_id = %1 ";

    queryStr += "order by c.id, f.id";

    queryStr = queryStr.arg(id);

//    qDebug() << queryStr;

    recommendationQueryModel->setQuery(queryStr);

    recommendationModel->setHeaderData(4, Qt::Horizontal, tr("Category"));
    recommendationModel->setHeaderData(5, Qt::Horizontal, tr("Property"));
    recommendationModel->setHeaderData(6, Qt::Horizontal, tr("Parameter"));
    recommendationModel->setHeaderData(7, Qt::Horizontal, tr("Actions / Recommendations"));

    recommendationTableViewDataBind(1, 5, 3, 4, 6, 2);

    ui->recommendationTableView->setColumnHidden(0, true);
    ui->recommendationTableView->setColumnHidden(1, true);
    ui->recommendationTableView->setColumnHidden(2, true);
    ui->recommendationTableView->setColumnHidden(3, true);

    ui->recommendationTableView->setColumnWidth(4, 150);
    ui->recommendationTableView->setColumnWidth(5, 150);
    ui->recommendationTableView->setColumnWidth(6, 200);
    ui->recommendationTableView->setColumnWidth(7, 400);

    ui->recommendationTableView->resizeRowsToContents();    
}

void MainWindow::recommendationTableViewDataBind(int fieldIdColumn, int fieldColumn, int categoryIdColumn, int categoryColumn, int parameterIdColumn, int fieldKeyColumn)
{
    ui->recommendationTableView->clearSpans();

    recommendationModel->fieldColumn = fieldColumn;
    recommendationModel->fieldKeyColumn = fieldKeyColumn;
    recommendationModel->categoryColumn = categoryColumn;
    recommendationModel->parameterIdColumn = parameterIdColumn;

    int currentCategoryId = -1;
    int categoryStartIndex = -1;
    int categoryIndex = 0;
    int categoryCount = 0;

    int currentFieldId = -1;
    int fieldStartIndex = -1;
    int fieldIndex = 0;
    int fieldCount = 0;

    QMap<int, QColor> fieldMap;
    QMap<int, QColor> categoryMap;

    for(int i = 0; i < recommendationQueryModel->rowCount(); i++)
    {
        QModelIndex fieldIdIndex = recommendationQueryModel->index(i, fieldIdColumn);

        int fieldId = recommendationQueryModel->data(fieldIdIndex).toInt();

        if(fieldId != currentFieldId)
        {
            if(currentFieldId >= 0 && fieldCount > 1)
            {
                ui->recommendationTableView->setSpan(fieldStartIndex, fieldColumn, fieldCount, 1);
            }

            currentFieldId = fieldId;

            fieldStartIndex = i;

            fieldCount = 1;

            fieldIndex++;
        }
        else
        {
            fieldCount++;
        }

        QModelIndex categoryIdIndex = recommendationQueryModel->index(i, categoryIdColumn);

        int categoryId = recommendationQueryModel->data(categoryIdIndex).toInt();

        if(categoryId != currentCategoryId)
        {
            if(currentCategoryId >= 0 && categoryCount > 1)
            {
                ui->recommendationTableView->setSpan(categoryStartIndex, categoryColumn, categoryCount, 1);
            }

            currentCategoryId = categoryId;

            categoryStartIndex = i;

            categoryCount = 1;

            categoryIndex++;
        }
        else
        {
            categoryCount++;
        }

        fieldMap[i] = fieldIndex % 2 == 0 ? QColor("white") : QColor(219, 255, 134);
        categoryMap[i] = categoryIndex % 2 == 0 ? QColor("white") : QColor(200, 255, 194);
    }

    if(currentFieldId >= 0 && fieldCount > 1)
    {
        ui->recommendationTableView->setSpan(fieldStartIndex, fieldColumn, fieldCount, 1);
    }

    if(currentCategoryId >= 0 && categoryCount > 1)
    {
        ui->recommendationTableView->setSpan(categoryStartIndex, categoryColumn, categoryCount, 1);
    }

    recommendationModel->fieldMap = fieldMap;
    recommendationModel->categoryMap = categoryMap;
}
