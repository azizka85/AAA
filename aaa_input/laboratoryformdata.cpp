#include <QDebug>

#include "laboratoryformdata.h"

LaboratoryFormData::LaboratoryFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new LaboratoryDataForm(parent);
}

LaboratoryFormData::~LaboratoryFormData()
{
    qDebug() << "LaboratoryFormData is destroyed";

    delete form;
}

QWidget *LaboratoryFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void LaboratoryFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
