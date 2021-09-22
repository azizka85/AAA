#ifndef MINERALOGYFORMDATA_H
#define MINERALOGYFORMDATA_H

#include "mainwindow.h"

#include "mineralogydataform.h"

class MineralogyFormData : public FormData
{
public:
    MineralogyFormData(QString title, QWidget *parent);
    ~MineralogyFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);

    virtual void saveFormData(QMap<QString, QVariant>& formData);

protected:
    MineralogyDataForm *form;\
};

#endif // MINERALOGYFORMDATA_H
