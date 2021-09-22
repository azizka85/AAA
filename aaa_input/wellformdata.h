#ifndef WELLFORMDATA_H
#define WELLFORMDATA_H

#include "mainwindow.h"

#include "formdata.h"

#include "welldataform.h"

class WellFormData : public FormData
{
public:
    WellFormData(QString title, QWidget* parent);
    ~WellFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);

    virtual void saveFormData(QMap<QString, QVariant>& formData);

protected:
    WellDataForm *form;\
};

#endif // WELLFORMDATA_H
