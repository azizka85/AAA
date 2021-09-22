#include <QDebug>

#include "mineralogydataform.h"
#include "ui_mineralogydataform.h"

MineralogyDataForm::MineralogyDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MineralogyDataForm)
{
    ui->setupUi(this);

    QRegExp regExp("^0\\.[0-9]+$");

    QRegExpValidator* regValidator = new QRegExpValidator(regExp, this);

    ui->md_clay_content_lineedit->setValidator(regValidator);


    formationTypeModel = new QSqlQueryModel(this);

    ui->md_formation_types_combobox->setModel(formationTypeModel);


    clayTypeModel = new QSqlQueryModel(this);

    ui->md_clays_types_combobox->setModel(clayTypeModel);


    formationDamageQueryModel = new QSqlQueryModel(this);

    formationDamageModel = new ParameterDataWithCategoryModel(this);

    formationDamageModel->setSourceModel(formationDamageQueryModel);

    ui->pd_formation_damage_tableview->setModel(formationDamageModel);
}

MineralogyDataForm::~MineralogyDataForm()
{
    delete ui;

    qDebug() << "MineralogyDataForm is destroyed";
}

void MineralogyDataForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    formationTypeModel->setQuery("select id, name_en from formation_types");

    ui->md_formation_types_combobox->setModelColumn(1);

    ui->md_formation_types_combobox->setCurrentIndex(0);


    clayTypeModel->setQuery("select id, name_en from clays_types");

    ui->md_clays_types_combobox->setModelColumn(1);

    ui->md_clays_types_combobox->setCurrentIndex(0);


    formationDamageQueryModel->setQuery("select fd.id, fd.type_id, fdt.name_en, fd.name_en from formation_damage fd, formation_damage_type fdt where fdt.id = fd.type_id order by fd.type_id");

    formationDamageModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    formationDamageModel->setHeaderData(3, Qt::Horizontal, tr("Name"));

    tableViewDataBind(1, 2);

    ui->pd_formation_damage_tableview->setColumnHidden(0, true);
    ui->pd_formation_damage_tableview->setColumnHidden(1, true);

    ui->pd_formation_damage_tableview->setColumnWidth(2, 125);
    ui->pd_formation_damage_tableview->setColumnWidth(3, 125);

    ui->pd_formation_damage_tableview->resizeRowsToContents();

    if(formData.contains("md_formation_types")) formationTypeDataBind(formData["md_formation_types"].toInt());

    if(formData.contains("md_clays_types")) clayTypeDataBind(formData["md_clays_types"].toInt());

    if(formData.contains("md_clay_content")) ui->md_clay_content_lineedit->setText(formData["md_clay_content"].toString());

    if(formData.contains("md_cementing_material_carbonate")) ui->md_cementing_material_carbonate_checkbox->setChecked(formData["md_cementing_material_carbonate"].toBool());

    if(formData.contains("pd_formation_damage")) formationDamageDataBind(formData["pd_formation_damage"].toList());
}

void MineralogyDataForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["md_formation_types"] = formationTypeSaveData();

    formData["md_clays_types"] = clayTypeSaveData();

    formData["md_clay_content"] = ui->md_clay_content_lineedit->text();

    formData["md_cementing_material_carbonate"] = ui->md_cementing_material_carbonate_checkbox->isChecked();

    formData["pd_formation_damage"] = formationDamageSaveData();
}

void MineralogyDataForm::tableViewDataBind(int categoryIdColumn, int categoryColumn)
{
    ui->pd_formation_damage_tableview->clearSpans();

    formationDamageModel->categoryColumn = categoryColumn;

    int currentCategoryId = -1;
    int categoryStartIndex = -1;
    int categoryIndex = 0;
    int categoryCount = 0;

    QMap<int, QColor> categoryMap;

    for(int i = 0; i < formationDamageQueryModel->rowCount(); i++)
    {
        QModelIndex categoryIdIndex = formationDamageQueryModel->index(i, categoryIdColumn);

        int categoryId = formationDamageQueryModel->data(categoryIdIndex).toInt();

        if(categoryId != currentCategoryId)
        {
            if(currentCategoryId >= 0 && categoryCount > 1)
            {
                ui->pd_formation_damage_tableview->setSpan(categoryStartIndex, categoryColumn, categoryCount, 1);
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

        categoryMap[i] = categoryIndex % 2 == 0 ? QColor("white") : QColor(200, 255, 194);
    }

    if(currentCategoryId >= 0 && categoryCount > 1)
    {
        ui->pd_formation_damage_tableview->setSpan(categoryStartIndex, categoryColumn, categoryCount, 1);
    }

    formationDamageModel->categoryMap = categoryMap;
}

void MineralogyDataForm::formationTypeDataBind(int id)
{
    for(int i = 0; i < formationTypeModel->rowCount(); i++)
    {
        int cid = formationTypeModel->index(i, 0).data().toInt();

        if(id == cid)
        {
            ui->md_formation_types_combobox->setCurrentIndex(i);

            break;
        }
    }
}

int MineralogyDataForm::formationTypeSaveData()
{
    int index = ui->md_formation_types_combobox->currentIndex();

    if(index >= 0) return formationTypeModel->index(index, 0).data().toInt();

    return 0;
}

void MineralogyDataForm::clayTypeDataBind(int id)
{
    for(int i = 0; i < clayTypeModel->rowCount(); i++)
    {
        int cid = clayTypeModel->index(i, 0).data().toInt();

        if(id == cid)
        {
            ui->md_clays_types_combobox->setCurrentIndex(i);

            break;
        }
    }
}

int MineralogyDataForm::clayTypeSaveData()
{
    int index = ui->md_clays_types_combobox->currentIndex();

    if(index >= 0) return clayTypeModel->index(index, 0).data().toInt();

    return 0;
}

void MineralogyDataForm::formationDamageDataBind(QList<QVariant> idList)
{
    for(int i = 0; i < formationDamageQueryModel->rowCount(); i++)
    {
        QModelIndex index = formationDamageQueryModel->index(i, 0);

        int id = index.data().toInt();

        if(idList.contains(id))
        {
            QModelIndex nameIndex = formationDamageQueryModel->index(i, 3);

            ui->pd_formation_damage_tableview->selectionModel()->select(nameIndex, QItemSelectionModel::Select);
        }
    }
}

QList<QVariant> MineralogyDataForm::formationDamageSaveData()
{
    QModelIndexList list = ui->pd_formation_damage_tableview->selectionModel()->selectedIndexes();

    int count = list.count();

    QList<QVariant> idList;

    for(int i = 0; i < count; i++)
    {
        QModelIndex index = list[i];

        int row = index.row();

        idList << formationDamageQueryModel->index(row, 0).data();
    }

    return idList;
}
