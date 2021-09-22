#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "parameterdata.h"

#include "settings.h"

ParameterData::ParameterData(QString queryStr)
{
    m_QueryStr = queryStr;
}

QString ParameterData::text(int parameterId) const
{
    QString val;

    QSqlQuery query = execQuery(parameterId);

    while(query.next())
    {
        val = query.value(0).toString();
    }

    return val;
}

ParameterData::~ParameterData()
{
    //    qDebug() << "ParameterData is destroyed";
}

QSqlQuery ParameterData::execQuery(int parameterId) const
{
    QString queryStr = m_QueryStr.arg(Settings::get()->shortLocale()).arg(parameterId);

    QSqlQuery query;

    query.prepare(queryStr);

    bool queryExecuted = query.exec();

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    return query;
}
