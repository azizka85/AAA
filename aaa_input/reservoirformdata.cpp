#include <QDebug>

#include "reservoirformdata.h"

ReservoirFormData::ReservoirFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new ReservoirDataForm(parent);
}

ReservoirFormData::~ReservoirFormData()
{
    qDebug() << "ReservoirFormData is destroyed";

    delete form;
}

QWidget *ReservoirFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant>& formData)
{
    form->display(formMap, formData);

    return form;
}

void ReservoirFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
