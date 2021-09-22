#include <QDebug>

#include "productiondataform.h"
#include "ui_productiondataform.h"

ProductionDataForm::ProductionDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductionDataForm)
{
    ui->setupUi(this);

    QRegExp exp("^0\\.[0-9]+$");

    QRegExpValidator* regValidator = new QRegExpValidator(exp, this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->pd_water_cut_lineedit->setValidator(regValidator);

    ui->pd_productivity_index_lineedit->setValidator(validator);

    ui->pd_damage_radius_lineedit->setValidator(validator);

    ui->pd_production_rate_lineedit->setValidator(validator);

    ui->pd_pumping_rate_lineedit->setValidator(validator);

    ui->pd_h2s_lineedit->setValidator(regValidator);

    ui->pd_bo_lineedit->setValidator(validator);

    ui->pd_viscosity_lineedit->setValidator(validator);

    ui->pd_specific_gravity_lineedit->setValidator(validator);
}

ProductionDataForm::~ProductionDataForm()
{
    delete ui;

    qDebug() << "ProductionDataForm is destroyed";
}

void ProductionDataForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("pd_water_cut")) ui->pd_water_cut_lineedit->setText(formData["pd_water_cut"].toString());

    if(formData.contains("pd_productivity_index")) ui->pd_productivity_index_lineedit->setText(formData["pd_productivity_index"].toString());

    if(formData.contains("pd_damage_radius")) ui->pd_damage_radius_lineedit->setText(formData["pd_damage_radius"].toString());

    if(formData.contains("pd_gas_lift_mandrel")) ui->pd_gas_lift_mandrel_checkbox->setChecked(formData["pd_gas_lift_mandrel"].toBool());

    if(formData.contains("pd_oil_contain_asphaltin")) ui->pd_oil_contain_asphaltin_checkbox->setChecked(formData["pd_oil_contain_asphaltin"].toBool());

    if(formData.contains("pd_oil_contain_paraffin")) ui->pd_oil_contain_paraffin_checkbox->setChecked(formData["pd_oil_contain_paraffin"].toBool());

    if(formData.contains("pd_production_rate")) ui->pd_production_rate_lineedit->setText(formData["pd_production_rate"].toString());

    if(formData.contains("pd_pumping_rate")) ui->pd_pumping_rate_lineedit->setText(formData["pd_pumping_rate"].toString());

    if(formData.contains("pd_h2s")) ui->pd_h2s_lineedit->setText(formData["pd_h2s"].toString());

    if(formData.contains("pd_bo")) ui->pd_bo_lineedit->setText(formData["pd_bo"].toString());

    if(formData.contains("pd_viscosity")) ui->pd_viscosity_lineedit->setText(formData["pd_viscosity"].toString());

    if(formData.contains("pd_specific_gravity")) ui->pd_specific_gravity_lineedit->setText(formData["pd_specific_gravity"].toString());
}

void ProductionDataForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["pd_water_cut"] = ui->pd_water_cut_lineedit->text();

    formData["pd_productivity_index"] = ui->pd_productivity_index_lineedit->text();

    formData["pd_damage_radius"] = ui->pd_damage_radius_lineedit->text();

    formData["pd_gas_lift_mandrel"] = ui->pd_gas_lift_mandrel_checkbox->isChecked();

    formData["pd_oil_contain_asphaltin"] = ui->pd_oil_contain_asphaltin_checkbox->isChecked();

    formData["pd_oil_contain_paraffin"] = ui->pd_oil_contain_paraffin_checkbox->isChecked();

    formData["pd_production_rate"] = ui->pd_production_rate_lineedit->text();

    formData["pd_pumping_rate"] = ui->pd_pumping_rate_lineedit->text();

    formData["pd_h2s"] = ui->pd_h2s_lineedit->text();

    formData["pd_bo"] = ui->pd_bo_lineedit->text();

    formData["pd_viscosity"] = ui->pd_viscosity_lineedit->text();

    formData["pd_specific_gravity"] = ui->pd_specific_gravity_lineedit->text();
}
