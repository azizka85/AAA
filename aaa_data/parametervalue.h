#ifndef PARAMETERVALUE_H
#define PARAMETERVALUE_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>

#include "parametervalueform.h"

class ParameterValue
{
public:
    ParameterValue(QString queryStr, QString createQueryStr, QString updateQueryStr);

    ~ParameterValue();

    virtual QWidget* display(int id = -1, int parameterId = -1, QString recommendation = QString(), QVBoxLayout *parent = 0);

    virtual void acceptCreate(int recommendationFromId, QString fieldKey);

    virtual void acceptEdit();

protected:
    QString m_QueryStr;
    QString m_CreateQueryStr;
    QString m_UpdateQueryStr;

    ParameterValueForm *form;
};

#endif // PARAMETERVALUE_H
