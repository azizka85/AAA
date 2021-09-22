#include <QDebug>

#include "picklingformdata.h"

PicklingFormData::PicklingFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new PicklingForm(parent);
}

PicklingFormData::~PicklingFormData()
{
    qDebug() << "PicklingFormData is destroyed";

    delete form;
}

QWidget *PicklingFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void PicklingFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
