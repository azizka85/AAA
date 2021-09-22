#ifndef PARAMETERDATAWITHTYPE_H
#define PARAMETERDATAWITHTYPE_H

#include "parameterdata.h"

class ParameterDataWithType : public ParameterData
{
public:
    ParameterDataWithType(QString queryStr);

    virtual QString text(int parameterId) const;
};

#endif // PARAMETERDATAWITHTYPE_H
