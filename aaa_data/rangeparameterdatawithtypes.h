#ifndef RANGEPARAMETERDATAWITHTYPES_H
#define RANGEPARAMETERDATAWITHTYPES_H

#include "parameterdata.h"

class RangeParameterDataWithTypes : public ParameterData
{
public:
    RangeParameterDataWithTypes(QString queryStr);

    virtual QString text(int parameterId) const;
};

#endif // RANGEPARAMETERDATAWITHTYPES_H
