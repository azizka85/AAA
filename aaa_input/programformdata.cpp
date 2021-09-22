#include <QDebug>

#include "programformdata.h"

ProgramFormData::ProgramFormData(QString title, QWidget *parent) : FormData(title)
{
    form = new ProgramForm(parent);
}

ProgramFormData::~ProgramFormData()
{
    qDebug() << "ProgramFormData is destroyed";

    delete form;
}

QWidget *ProgramFormData::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    form->display(formMap, formData);

    return form;
}

void ProgramFormData::saveFormData(QMap<QString, QVariant> &formData)
{
    form->saveFormData(formData);
}
