#ifndef PICKLINGFORMDATA_H
#define PICKLINGFORMDATA_H

#include "formdata.h"

#include "picklingform.h"

class PicklingFormData : public FormData
{
public:
    PicklingFormData(QString title, QWidget *parent);
    ~PicklingFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    PicklingForm* form;
};

#endif // PICKLINGFORMDATA_H
