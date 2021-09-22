#include <QDebug>

#include "overflushform.h"
#include "ui_overflushform.h"

OverFlushForm::OverFlushForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverFlushForm)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->ofa_density_lineedit->setValidator(validator);

    ui->ofa_pumping_pressure_lineedit->setValidator(validator);

    ui->ofa_pumping_rate_lineedit->setValidator(validator);

    ui->ofa_viscosity_lineedit->setValidator(validator);

    ui->ofa_volume_lineedit->setValidator(validator);
}

OverFlushForm::~OverFlushForm()
{
    qDebug() << "OverFlushForm is destroyed";

    delete ui;
}

void OverFlushForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("ofa_volume")) ui->ofa_volume_lineedit->setText(formData["ofa_volume"].toString());

    if(formData.contains("ofa_viscosity")) ui->ofa_viscosity_lineedit->setText(formData["ofa_viscosity"].toString());

    if(formData.contains("ofa_density")) ui->ofa_density_lineedit->setText(formData["ofa_density"].toString());

    if(formData.contains("ofa_treatment")) ui->ofa_treatment_lineedit->setText(formData["ofa_treatment"].toString());

    if(formData.contains("ofa_pumping_pressure")) ui->ofa_pumping_pressure_lineedit->setText(formData["ofa_pumping_pressure"].toString());

    if(formData.contains("ofa_pumping_rate")) ui->ofa_pumping_rate_lineedit->setText(formData["ofa_pumping_rate"].toString());
}

void OverFlushForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["ofa_volume"] = ui->ofa_volume_lineedit->text();

    formData["ofa_viscosity"] = ui->ofa_viscosity_lineedit->text();

    formData["ofa_density"] = ui->ofa_density_lineedit->text();

    formData["ofa_treatment"] = ui->ofa_treatment_lineedit->text();

    formData["ofa_pumping_pressure"] = ui->ofa_pumping_pressure_lineedit->text();

    formData["ofa_pumping_rate"] = ui->ofa_pumping_rate_lineedit->text();
}
