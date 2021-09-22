#include <QtMath>
#include <QDebug>

#include "reservoirdataform.h"
#include "ui_reservoirdataform.h"

ReservoirDataForm::ReservoirDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReservoirDataForm)
{
    Kd = 0;
    Rd = 0;
    Rw = 0;

    ui->setupUi(this);

    QRegExp exp("^0\\.[0-9]+$");

    QRegExpValidator* regValidator = new QRegExpValidator(exp, this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->rd_porosity_lineedit->setValidator(regValidator);

    ui->rd_reservoir_permeability_lineedit->setValidator(validator);

    ui->rd_reservoir_pressure_lineedit->setValidator(validator);

    ui->rd_reservoir_temperature_lineedit->setValidator(validator);

    ui->rd_fracture_pressure_lineedit->setValidator(validator);

    ui->rd_pumping_pressure_lineedit->setValidator(validator);

    ui->rd_gas_oil_contact_lineedit->setValidator(validator);

    ui->rd_skin_factor_lineedit->setValidator(validator);

    ui->rd_drainage_radius_lineedit->setValidator(validator);


    reservoirTypeModel = new QSqlQueryModel(this);

    ui->rd_permeability_type_listview->setModel(reservoirTypeModel);


    driveMechanismModel = new QSqlQueryModel(this);

    ui->rd_drive_mechanism_listview->setModel(driveMechanismModel);
}

ReservoirDataForm::~ReservoirDataForm()
{
    delete ui;

    qDebug() << "ReservoirDataForm is destroyed";
}

void ReservoirDataForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    reservoirTypeModel->setQuery("select id, name_en from reservoir_permeability");

    ui->rd_permeability_type_listview->setColumnHidden(0, true);
    ui->rd_permeability_type_listview->setColumnWidth(1, 200);


    driveMechanismModel->setQuery("select id, name_en from drive_mechanism");

    ui->rd_drive_mechanism_listview->setColumnHidden(0, true);
    ui->rd_drive_mechanism_listview->setColumnWidth(1, 200);


    if(formData.contains("rd_permeability_type")) reservoirTypeDataBind(formData["rd_permeability_type"].toList());

    if(formData.contains("rd_drive_mechanism")) driveMechanismDataBind(formData["rd_drive_mechanism"].toList());


    if(formData.contains("rd_porosity")) ui->rd_porosity_lineedit->setText(formData["rd_porosity"].toString());

    if(formData.contains("rd_reservoir_permeability")) ui->rd_reservoir_permeability_lineedit->setText(formData["rd_reservoir_permeability"].toString());

    if(formData.contains("rd_reservoir_pressure")) ui->rd_reservoir_pressure_lineedit->setText(formData["rd_reservoir_pressure"].toString());

    if(formData.contains("rd_reservoir_temperature")) ui->rd_reservoir_temperature_lineedit->setText(formData["rd_reservoir_temperature"].toString());

    if(formData.contains("rd_fracture_pressure")) ui->rd_fracture_pressure_lineedit->setText(formData["rd_fracture_pressure"].toString());

    if(formData.contains("rd_pumping_pressure")) ui->rd_pumping_pressure_lineedit->setText(formData["rd_pumping_pressure"].toString());

    if(formData.contains("rd_gas_oil_contact")) ui->rd_gas_oil_contact_lineedit->setText(formData["rd_gas_oil_contact"].toString());

    if(formData.contains("rd_skin_factor")) ui->rd_skin_factor_lineedit->setText(formData["rd_skin_factor"].toString());

    if(formData.contains("rd_drainage_radius")) ui->rd_drainage_radius_lineedit->setText(formData["rd_drainage_radius"].toString());

    if(formData.contains("wd_well_bore_radius")) Rw = formData["wd_well_bore_radius"].toDouble();

    if(formData.contains("pd_damage_radius")) Rd = formData["pd_damage_radius"].toDouble();

    if(formData.contains("cd_kd")) Kd = formData["cd_kd"].toDouble();

    calculate();
}

void ReservoirDataForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["rd_permeability_type"] = reservoirTypeSaveData();

    formData["rd_drive_mechanism"] = driveMechanismSaveData();


    formData["rd_porosity"] = ui->rd_porosity_lineedit->text();

    formData["rd_reservoir_permeability"] = ui->rd_reservoir_permeability_lineedit->text();

    formData["rd_reservoir_pressure"] = ui->rd_reservoir_pressure_lineedit->text();

    formData["rd_reservoir_temperature"] = ui->rd_reservoir_temperature_lineedit->text();

    formData["rd_fracture_pressure"] = ui->rd_fracture_pressure_lineedit->text();

    formData["rd_pumping_pressure"] = ui->rd_pumping_pressure_lineedit->text();

    formData["rd_gas_oil_contact"] = ui->rd_gas_oil_contact_lineedit->text();

    formData["rd_skin_factor"] = ui->rd_skin_factor_lineedit->text();

    formData["rd_drainage_radius"] = ui->rd_drainage_radius_lineedit->text();
}

void ReservoirDataForm::textEdited()
{
    calculate();
}

void ReservoirDataForm::reservoirTypeDataBind(QList<QVariant> idList)
{
    for(int i = 0; i < reservoirTypeModel->rowCount(); i++)
    {
        QModelIndex index = reservoirTypeModel->index(i, 0);

        int id = index.data().toInt();

        if(idList.contains(id))
        {
            QModelIndex nameIndex = reservoirTypeModel->index(i, 1);

            ui->rd_permeability_type_listview->selectionModel()->select(nameIndex, QItemSelectionModel::Select);
        }
    }
}

QList<QVariant> ReservoirDataForm::reservoirTypeSaveData()
{
    QModelIndexList list = ui->rd_permeability_type_listview->selectionModel()->selectedIndexes();

    int count = list.count();

    QList<QVariant> idList;

    for(int i = 0; i < count; i++)
    {
        QModelIndex index = list[i];

        int row = index.row();

        idList << reservoirTypeModel->index(row, 0).data();
    }

    return idList;
}

void ReservoirDataForm::driveMechanismDataBind(QList<QVariant> idList)
{
    for(int i = 0; i < driveMechanismModel->rowCount(); i++)
    {
        QModelIndex index = driveMechanismModel->index(i, 0);

        int id = index.data().toInt();

        if(idList.contains(id))
        {
            QModelIndex nameIndex = driveMechanismModel->index(i, 1);

            ui->rd_drive_mechanism_listview->selectionModel()->select(nameIndex, QItemSelectionModel::Select);
        }
    }
}

QList<QVariant> ReservoirDataForm::driveMechanismSaveData()
{
    QModelIndexList list = ui->rd_drive_mechanism_listview->selectionModel()->selectedIndexes();

    int count = list.count();

    QList<QVariant> idList;

    for(int i = 0; i < count; i++)
    {
        QModelIndex index = list[i];

        int row = index.row();

        idList << driveMechanismModel->index(row, 0).data();
    }

    return idList;
}

void ReservoirDataForm::calculate()
{
    double K = ui->rd_reservoir_permeability_lineedit->text().toDouble();

    double S = (K/Kd - 1)*qLn(Rd/Rw);

    ui->rd_skin_factor_lineedit->setText(QString::number(S));
}
