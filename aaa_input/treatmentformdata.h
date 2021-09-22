#ifndef TREATMENTFORMDATA_H
#define TREATMENTFORMDATA_H

#include "formdata.h"

#include "treatmentdesignform.h"

class TreatmentFormData : public FormData
{
public:
    TreatmentFormData(QString title, QWidget *parent);
    ~TreatmentFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    TreatmentDesignForm* form;
};

#endif // TREATMENTFORMDATA_H
