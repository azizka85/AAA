#ifndef PARAMETERVALUEWITHTYPE_H
#define PARAMETERVALUEWITHTYPE_H

#include "parametervaluewithtypeform.h"

class ParameterValueWithType : public ParameterValue
{
public:
    ParameterValueWithType(QString queryStr, QString typeIdQueryStr, QString typeQueryStr, QString createQueryStr, QString updateQueryStr);
    ~ParameterValueWithType();

    virtual QWidget* display(int id = -1, int parameterId = -1, QString recommendation = QString(), QVBoxLayout *parent = 0);

    virtual void acceptCreate(int recommendationFromId, QString fieldKey);

    virtual void acceptEdit();

protected:
    QString m_QueryStr;
    QString m_TypeIdQueryStr;
    QString m_TypeQueryStr;
    QString m_CreateQueryStr;
    QString m_UpdateQueryStr;

    ParameterValueWithTypeForm *form;
};

#endif // PARAMETERVALUEWITHTYPE_H
