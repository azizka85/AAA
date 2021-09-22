#ifndef LABORATORYFORMDATA_H
#define LABORATORYFORMDATA_H

#include "mainwindow.h"

#include "laboratorydataform.h"

class LaboratoryFormData : public FormData
{
public:
    LaboratoryFormData(QString title, QWidget *parent);
    ~LaboratoryFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    virtual void saveFormData(QMap<QString, QVariant>& formData);

protected:
    LaboratoryDataForm *form;\
};

#endif // LABORATORYFORMDATA_H
