#ifndef PRODUCTIONFORMDATA_H
#define PRODUCTIONFORMDATA_H

#include "mainwindow.h"

#include "formdata.h"

#include "productiondataform.h"

class ProductionFormData : public FormData
{
public:
    ProductionFormData(QString title, QWidget* parent);
    ~ProductionFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);

    virtual void saveFormData(QMap<QString, QVariant>& formData);

protected:
    ProductionDataForm *form;\
};

#endif // PRODUCTIONFORMDATA_H
