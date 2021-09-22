#ifndef COMPARISONPARAMETERDATA_H
#define COMPARISONPARAMETERDATA_H

#include "parameterdata.h"

class ComparisonParameterData : public ParameterData
{
public:
    ComparisonParameterData(QString queryStr);

    virtual QString text(int parameterId) const;

protected:
    QString m_QueryStr;
};

#endif // COMPARISONPARAMETERDATA_H
