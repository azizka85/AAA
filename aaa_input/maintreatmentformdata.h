#ifndef MAINTREATMENTFORMDATA_H
#define MAINTREATMENTFORMDATA_H

#include "formdata.h"

#include "maintreatmentform.h"

class MainTreatmentFormData : public FormData
{
public:
    MainTreatmentFormData(QString title, QWidget *parent);
    ~MainTreatmentFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    MainTreatmentForm* form;
};

#endif // MAINTREATMENTFORMDATA_H
