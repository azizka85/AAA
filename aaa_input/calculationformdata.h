#ifndef CALCULATIONFORMDATA_H
#define CALCULATIONFORMDATA_H

#include "formdata.h"

#include "calculationdataform.h"

class CalculationFormData : public FormData
{
public:
    CalculationFormData(QString title, QWidget *parent);
    ~CalculationFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    CalculationDataForm *form;
};

#endif // CALCULATIONFORMDATA_H
