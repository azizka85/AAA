#include <QDebug>

#include "productionformdata.h"

ProductionFormData::ProductionFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new ProductionDataForm(parent);
}

ProductionFormData::~ProductionFormData()
{
    qDebug() << "ProductionFormData is destroyed";

    delete form;
}

QWidget *ProductionFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant>& formData)
{
    form->display(formMap, formData);

    return form;
}

void ProductionFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
