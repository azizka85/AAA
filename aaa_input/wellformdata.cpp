#include <QDebug>

#include "wellformdata.h"

WellFormData::WellFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new WellDataForm(parent);
}

WellFormData::~WellFormData()
{
    qDebug() << "WellFormData is destroyed";

    delete form;
}

QWidget *WellFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant>& formData)
{
    form->display(formMap, formData);

    return form;
}

void WellFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
