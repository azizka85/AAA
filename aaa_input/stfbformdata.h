#ifndef STFBFORMDATA_H
#define STFBFORMDATA_H

#include "formdata.h"

#include "stfbform.h"

class STFBFormData : public FormData
{
public:
    STFBFormData(QString title, QWidget *parent);
    ~STFBFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    STFBForm* form;
};

#endif // STFBFORMDATA_H
