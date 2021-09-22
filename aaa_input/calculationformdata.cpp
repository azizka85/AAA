#include <QDebug>

#include "calculationformdata.h"

CalculationFormData::CalculationFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new CalculationDataForm(parent);
}

CalculationFormData::~CalculationFormData()
{
    qDebug() << "CalculationFormData is destroyed";

    delete form;
}

QWidget *CalculationFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void CalculationFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
