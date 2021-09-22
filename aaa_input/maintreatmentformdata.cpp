#include <QDebug>

#include "maintreatmentformdata.h"

MainTreatmentFormData::MainTreatmentFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new MainTreatmentForm(parent);
}

MainTreatmentFormData::~MainTreatmentFormData()
{
    qDebug() << "MainTreatmentFormData is destroyed";

    delete form;
}

QWidget *MainTreatmentFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void MainTreatmentFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
