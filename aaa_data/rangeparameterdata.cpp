#include <QVariant>

#include "rangeparameterdata.h"

RangeParameterData::RangeParameterData(QString shortName, QString queryStr) : ParameterData(queryStr)
{
    m_ShortName = shortName;
}

QString RangeParameterData::text(int parameterId) const
{
    QString val = m_ShortName;

    QSqlQuery query = execQuery(parameterId);

    while(query.next())
    {
        QVariant minVal = query.value(0);
        QVariant maxVal = query.value(1);

        if(!minVal.isNull()) val = minVal.toString() + " < " + val;

        if(!maxVal.isNull()) val = val + " < " + maxVal.toString();
    }

    return val;
}
