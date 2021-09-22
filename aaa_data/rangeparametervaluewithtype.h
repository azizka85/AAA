#ifndef RANGEPARAMETERVALUEWITHTYPE_H
#define RANGEPARAMETERVALUEWITHTYPE_H

#include "parametervalue.h"

#include "rangeparametervaluewithtypeform.h"

class RangeParameterValueWithType : public ParameterValue
{
public:
    RangeParameterValueWithType(double rangeMin, double rangeMax, int decimals,
        QString queryStr, QString typeIdQueryStr, QString typeQueryStr,
        QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr);

    ~RangeParameterValueWithType();

    virtual QWidget* display(int id = -1, int parameterId = -1, QString recommendation = QString(), QVBoxLayout *parent = 0);

    virtual void acceptCreate(int recommendationFromId, QString fieldKey);

    virtual void acceptEdit();

protected:
    double m_RangeMin;
    double m_RangeMax;
    int m_Decimals;

    QString m_QueryStr;
    QString m_TypeIdQueryStr;
    QString m_TypeQueryStr;
    QString m_CreateQueryStr;
    QString m_CreateParameterQueryStr;
    QString m_UpdateQueryStr;
    QString m_UpdateParameterQueryStr;

    RangeParameterValueWithTypeForm *form;
};

#endif // RANGEPARAMETERVALUEWITHTYPE_H
