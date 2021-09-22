#include <QDebug>

#include "laboratorydataform.h"
#include "ui_laboratorydataform.h"

LaboratoryDataForm::LaboratoryDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LaboratoryDataForm)
{
    ui->setupUi(this);

    compatibilityDataModel = new QSqlQueryModel(this);

    ui->ld_compatibility_data_listview->setModel(compatibilityDataModel);
}

LaboratoryDataForm::~LaboratoryDataForm()
{
    delete ui;

    qDebug() << "LaboratoryDataForm is destroyed";
}

void LaboratoryDataForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant>& formData)
{
    compatibilityDataModel->setQuery("select id, name_en from compatibility_data");    

    ui->ld_compatibility_data_listview->setColumnHidden(0, true);

    ui->ld_compatibility_data_listview->setColumnWidth(1, 500);

    ui->ld_compatibility_data_listview->resizeRowsToContents();

    if(formData.contains("ld_compatibility_data")) compatibilityDataBind(formData["ld_compatibility_data"].toList());
}

void LaboratoryDataForm::saveFormData(QMap<QString, QVariant> &formData)
{
    QModelIndexList list = ui->ld_compatibility_data_listview->selectionModel()->selectedIndexes();

    int count = list.count();

    QList<QVariant> idList;

    for(int i = 0; i < count; i++)
    {
        QModelIndex index = list[i];

        int row = index.row();

        idList << compatibilityDataModel->index(row, 0).data();
    }

    formData["ld_compatibility_data"] = QVariant(idList);
}

void LaboratoryDataForm::compatibilityDataBind(QList<QVariant> compatibilityDataIdList)
{
    for(int i = 0; i < compatibilityDataModel->rowCount(); i++)
    {
        QModelIndex index = compatibilityDataModel->index(i, 0);

        int id = index.data().toInt();

        if(compatibilityDataIdList.contains(id))
        {
            QModelIndex nameIndex = compatibilityDataModel->index(i, 1);

            ui->ld_compatibility_data_listview->selectionModel()->select(nameIndex, QItemSelectionModel::Select);
        }
    }
}
