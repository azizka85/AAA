#ifndef COMPARISONPARAMETERVALUE_H
#define COMPARISONPARAMETERVALUE_H

#include "parametervalue.h"

#include "comparisonparametervalueform.h"

class ComparisonParameterValue : public ParameterValue
{
public:
    ComparisonParameterValue(QString compareFieldQueryStr, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr);
    ~ComparisonParameterValue();

    virtual QWidget* display(int id = -1, int parameterId = -1, QString recommendation = QString(), QVBoxLayout *parent = 0);

    virtual void acceptCreate(int recommendationFromId, QString fieldKey);

    virtual void acceptEdit();

protected:
    QString m_CompareFieldQueryStr;
    QString m_QueryStr;
    QString m_CreateQueryStr;
    QString m_CreateParameterQueryStr;
    QString m_UpdateQueryStr;
    QString m_UpdateParameterQueryStr;

    ComparisonParameterValueForm *form;
};

#endif // COMPARISONPARAMETERVALUE_H
