#ifndef PREFLUSHFORMDATA_H
#define PREFLUSHFORMDATA_H

#include "formdata.h"

#include "preflushform.h"

class PreFlushFormData : public FormData
{
public:
    PreFlushFormData(QString title, QWidget *parent);
    ~PreFlushFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    PreFlushForm* form;
};

#endif // PREFLUSHFORMDATA_H
