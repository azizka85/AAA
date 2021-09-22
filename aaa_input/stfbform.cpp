#include <QDebug>

#include "stfbform.h"
#include "ui_stfbform.h"

STFBForm::STFBForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STFBForm)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->stfb_soaking_time_lineedit->setValidator(validator);
}

STFBForm::~STFBForm()
{
    qDebug() << "STFBForm is destroyed";

    delete ui;
}

void STFBForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("stfb_flow_back_type")) ui->stfb_flow_back_type_lineedit->setText(formData["stfb_flow_back_type"].toString());

    if(formData.contains("stfb_soaking_time")) ui->stfb_soaking_time_lineedit->setText(formData["stfb_soaking_time"].toString());
}

void STFBForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["stfb_flow_back_type"] = ui->stfb_flow_back_type_lineedit->text();

    formData["stfb_soaking_time"] = ui->stfb_soaking_time_lineedit->text();
}
