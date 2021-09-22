#include <QDebug>

#include "treatmentformdata.h"


TreatmentFormData::TreatmentFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new TreatmentDesignForm(parent);
}

TreatmentFormData::~TreatmentFormData()
{
    qDebug() << "TreatmentFormData is destroyed";
}

QWidget *TreatmentFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void TreatmentFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
