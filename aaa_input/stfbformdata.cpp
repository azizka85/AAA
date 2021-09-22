#include <QDebug>

#include "stfbformdata.h"

STFBFormData::STFBFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new STFBForm(parent);
}

STFBFormData::~STFBFormData()
{
    qDebug() << "STFBFormData is destroyed";

    delete form;
}

QWidget *STFBFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void STFBFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
