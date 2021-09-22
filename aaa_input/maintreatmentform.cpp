#include <QDebug>

#include "maintreatmentform.h"
#include "ui_maintreatmentform.h"

MainTreatmentForm::MainTreatmentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTreatmentForm)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->mta_density_lineedit->setValidator(validator);

    ui->mta_pumping_pressure_lineedit->setValidator(validator);

    ui->mta_pumping_rate_lineedit->setValidator(validator);

    ui->mta_pumping_treatment_lineedit->setValidator(validator);

    ui->mta_viscosity_lineedit->setValidator(validator);

    ui->mta_volume_lineedit->setValidator(validator);

    additivesModel = new UpdateModel(0, 2, this);

    ui->mta_additives_tableview->setModel(additivesModel);

    doubleDelegate = new DoubleEditorDelegate(this);
}

MainTreatmentForm::~MainTreatmentForm()
{
    qDebug() << "MainTreatmentForm is destroyed";

    delete ui;
}

void MainTreatmentForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("mta_additives")) additivesModel->setUpdateData(formData["mta_additives"].toMap());

    if(formData.contains("mta_volume")) ui->mta_volume_lineedit->setText(formData["mta_volume"].toString());

    if(formData.contains("mta_viscosity")) ui->mta_viscosity_lineedit->setText(formData["mta_viscosity"].toString());

    if(formData.contains("mta_pumping_pressure")) ui->mta_pumping_pressure_lineedit->setText(formData["mta_pumping_pressure"].toString());

    if(formData.contains("mta_pumping_rate")) ui->mta_pumping_rate_lineedit->setText(formData["mta_pumping_rate"].toString());

    if(formData.contains("mta_density")) ui->mta_density_lineedit->setText(formData["mta_density"].toString());

    if(formData.contains("mta_treatment")) ui->mta_treatment_lineedit->setText(formData["mta_treatment"].toString());

    if(formData.contains("mta_pumping_treatment")) ui->mta_pumping_treatment_lineedit->setText(formData["mta_pumping_treatment"].toString());

    additivesModel->setQuery("select id, name_en, null from acid_type");

    additivesModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    additivesModel->setHeaderData(2, Qt::Horizontal, tr("Value"));

    ui->mta_additives_tableview->setColumnHidden(0, true);

    ui->mta_additives_tableview->setColumnWidth(1, 300);
    ui->mta_additives_tableview->setColumnWidth(2, 300);

    ui->mta_additives_tableview->setItemDelegateForColumn(2, doubleDelegate);
}

void MainTreatmentForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["mta_volume"] = ui->mta_volume_lineedit->text();

    formData["mta_viscosity"] = ui->mta_viscosity_lineedit->text();

    formData["mta_pumping_pressure"] = ui->mta_pumping_pressure_lineedit->text();

    formData["mta_pumping_rate"] = ui->mta_pumping_rate_lineedit->text();

    formData["mta_density"] = ui->mta_density_lineedit->text();

    formData["mta_treatment"] = ui->mta_treatment_lineedit->text();

    formData["mta_pumping_treatment"] = ui->mta_pumping_treatment_lineedit->text();

    formData["mta_additives"] = additivesModel->updateData();
}
