#include <QDebug>

#include "treatmentdesignform.h"
#include "ui_treatmentdesignform.h"

TreatmentDesignForm::TreatmentDesignForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreatmentDesignForm)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->td_pickling_volume_lineedit->setValidator(validator);

    ui->td_pressure_test_lineedit->setValidator(validator);
}

TreatmentDesignForm::~TreatmentDesignForm()
{
    qDebug() << "TreatmentDesignForm is destroyed";

    delete ui;
}

void TreatmentDesignForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("td_pickling_volume")) ui->td_pickling_volume_lineedit->setText(formData["td_pickling_volume"].toString());

    if(formData.contains("td_pressure_test")) ui->td_pressure_test_lineedit->setText(formData["td_pressure_test"].toString());
}

void TreatmentDesignForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["td_pickling_volume"] = ui->td_pickling_volume_lineedit->text();

    formData["td_pressure_test"] = ui->td_pressure_test_lineedit->text();
}
