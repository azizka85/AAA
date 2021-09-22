#include <QDebug>

#include "mineralogyformdata.h"

MineralogyFormData::MineralogyFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new MineralogyDataForm(parent);       
}

MineralogyFormData::~MineralogyFormData()
{
    qDebug() << "MineralogyFormData is destroyed";

    delete form;
}

QWidget *MineralogyFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant>& formData)
{
    form->display(formMap, formData);

    return form;
}

void MineralogyFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
