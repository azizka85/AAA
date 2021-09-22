#include <QVariant>

#include "parameterdatawithtype.h"

ParameterDataWithType::ParameterDataWithType(QString queryStr) : ParameterData(queryStr)
{

}

QString ParameterDataWithType::text(int parameterId) const
{
    QString val;

    QSqlQuery query = execQuery(parameterId);

    while(query.next())
    {
        val = query.value(0).toString() + ": " + query.value(1).toString();
    }

    return val;
}
