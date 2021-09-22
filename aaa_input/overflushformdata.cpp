#include <QDebug>

#include "overflushformdata.h"

OverFlushFormData::OverFlushFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new OverFlushForm(parent);
}

OverFlushFormData::~OverFlushFormData()
{
    qDebug() << "OverFlushFormData is destroyed";

    delete form;
}

QWidget *OverFlushFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void OverFlushFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
