#include "settings.h"

#include "comparisonparameterdata.h"

ComparisonParameterData::ComparisonParameterData(QString queryStr) : ParameterData(queryStr)
{
    m_QueryStr = queryStr;
}

QString ComparisonParameterData::text(int parameterId) const
{
    QString val;

    QSqlQuery query = execQuery(parameterId);

    while(query.next())
    {
        val = query.value(0).toString();

        int criteriaId = query.value(1).toInt();

        val += " (" + Settings::get()->criteriaList.value(criteriaId) + ")";
    }

    return val;
}
