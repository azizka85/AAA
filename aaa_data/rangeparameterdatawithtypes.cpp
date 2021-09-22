#include <QVariant>

#include "rangeparameterdatawithtypes.h"

RangeParameterDataWithTypes::RangeParameterDataWithTypes(QString queryStr) : ParameterData(queryStr)
{

}

QString RangeParameterDataWithTypes::text(int parameterId) const
{
    QString val;

    QSqlQuery query = execQuery(parameterId);

    while(query.next())
    {
        val = query.value(0).toString();

        QVariant min = query.value(1);
        QVariant max = query.value(2);

        if(!min.isNull()) val = min.toString() + " < " + val;

        if(!max.isNull()) val = val + " < " + max.toString();
    }

    return val;
}
