#ifndef RANGEPARAMETERDATA_H
#define RANGEPARAMETERDATA_H

#include <QString>

#include "parameterdata.h"

class RangeParameterData : public ParameterData
{
public:
    RangeParameterData(QString shortName, QString queryStr);

    virtual QString text(int parameterId) const;

protected:
    QString m_ShortName;
};

#endif // RANGEPARAMETERDATA_H
