#ifndef PROGRAMFORMDATA_H
#define PROGRAMFORMDATA_H

#include "formdata.h"

#include "programform.h"

class ProgramFormData : public FormData
{
public:
    ProgramFormData(QString title, QWidget *parent);
    ~ProgramFormData();

    QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant>& formData);

protected:
    ProgramForm* form;
};

#endif // PROGRAMFORMDATA_H
