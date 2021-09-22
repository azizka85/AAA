#ifndef OVERFLUSHFORMDATA_H
#define OVERFLUSHFORMDATA_H

#include "formdata.h"

#include "overflushform.h"

class OverFlushFormData : public FormData
{
public:
    OverFlushFormData(QString title, QWidget *parent);
    ~OverFlushFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    OverFlushForm* form;
};

#endif // OVERFLUSHFORMDATA_H
