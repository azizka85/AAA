#include <QDebug>

#include "preflushformdata.h"

PreFlushFormData::PreFlushFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new PreFlushForm(parent);
}

PreFlushFormData::~PreFlushFormData()
{
    qDebug() << "PreFlushFormData is destroyed";

    delete form;
}

QWidget *PreFlushFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void PreFlushFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
