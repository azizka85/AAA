#ifndef RESERVOIRFORMDATA_H
#define RESERVOIRFORMDATA_H

#include "mainwindow.h"

#include "formdata.h"

#include "reservoirdataform.h"

class ReservoirFormData : public FormData
{
public:
    ReservoirFormData(QString title, QWidget *parent);
    ~ReservoirFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);

    virtual void saveFormData(QMap<QString, QVariant>& formData);

protected:
    ReservoirDataForm *form;
};

#endif // RESERVOIRFORMDATA_H
