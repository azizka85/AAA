#include <QDebug>

#include "preflushform.h"
#include "ui_preflushform.h"

PreFlushForm::PreFlushForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreFlushForm)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->pfa_density_lineedit->setValidator(validator);

    ui->pfa_pumping_pressure_lineedit->setValidator(validator);

    ui->pfa_pumping_rate_lineedit->setValidator(validator);

    ui->pfa_viscosity_lineedit->setValidator(validator);

    ui->pfa_volume_lineedit->setValidator(validator);
}

PreFlushForm::~PreFlushForm()
{
    qDebug() << "PreFlushForm is destroyed";

    delete ui;
}

void PreFlushForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("pfa_volume")) ui->pfa_volume_lineedit->setText(formData["pfa_volume"].toString());

    if(formData.contains("pfa_viscosity")) ui->pfa_viscosity_lineedit->setText(formData["pfa_viscosity"].toString());

    if(formData.contains("pfa_density")) ui->pfa_density_lineedit->setText(formData["pfa_density"].toString());

    if(formData.contains("pfa_treatment")) ui->pfa_treatment_lineedit->setText(formData["pfa_treatment"].toString());

    if(formData.contains("pfa_pumping_pressure")) ui->pfa_pumping_pressure_lineedit->setText(formData["pfa_pumping_pressure"].toString());

    if(formData.contains("pfa_pumping_rate")) ui->pfa_pumping_rate_lineedit->setText(formData["pfa_pumping_rate"].toString());
}

void PreFlushForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["pfa_volume"] = ui->pfa_volume_lineedit->text();

    formData["pfa_viscosity"] = ui->pfa_viscosity_lineedit->text();

    formData["pfa_density"] = ui->pfa_density_lineedit->text();

    formData["pfa_treatment"] = ui->pfa_treatment_lineedit->text();

    formData["pfa_pumping_pressure"] = ui->pfa_pumping_pressure_lineedit->text();

    formData["pfa_pumping_rate"] = ui->pfa_pumping_rate_lineedit->text();
}
