#ifndef RANGEPARAMETERVALUE_H
#define RANGEPARAMETERVALUE_H

#include "parametervalue.h"

#include "rangeparametervalueform.h"

class RangeParameterValue : public ParameterValue
{
public:
    RangeParameterValue(double rangeMin, double rangeMax, int decimals, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr);
    ~RangeParameterValue();

    virtual QWidget* display(int id = -1, int parameterId = -1, QString recommendation = QString(), QVBoxLayout *parent = 0);

    virtual void acceptCreate(int recommendationFromId, QString fieldKey);

    virtual void acceptEdit();

protected:
    double m_RangeMin;
    double m_RangeMax;
    int m_Decimals;

    QString m_QueryStr;
    QString m_CreateQueryStr;
    QString m_CreateParameterQueryStr;
    QString m_UpdateQueryStr;
    QString m_UpdateParameterQueryStr;

    RangeParameterValueForm *form;
};

#endif // RANGEPARAMETERVALUE_H
