#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "parametervalue.h"
#include "parametervaluewithtype.h"

ParameterValueWithType::ParameterValueWithType(QString queryStr, QString typeIdQueryStr, QString typeQueryStr, QString createQueryStr, QString updateQueryStr)
    : ParameterValue(queryStr, createQueryStr, updateQueryStr)
{
    m_QueryStr = queryStr;
    m_TypeIdQueryStr = typeIdQueryStr;
    m_TypeQueryStr = typeQueryStr;
    m_CreateQueryStr = createQueryStr;
    m_UpdateQueryStr = updateQueryStr;
}

ParameterValueWithType::~ParameterValueWithType()
{
    qDebug() << "ParameterValueWithType is destroyed";
}

QWidget *ParameterValueWithType::display(int id, int parameterId, QString recommendation, QVBoxLayout *parent)
{
    if(parent != 0)
    {
        int typeId = -1;

        if(parameterId >= 0)
        {
            QSqlQuery query;

            query.prepare(m_TypeIdQueryStr);
            query.addBindValue(parameterId);

            bool queryExecuted = query.exec();

            qDebug() << "Query executed: " << queryExecuted;

            if(!queryExecuted)
            {
                qDebug() << "Query execution error: " << query.lastError();
            }

            while(query.next())
            {
                typeId = query.value(0).toInt();
            }
        }

        form = new ParameterValueWithTypeForm(id, typeId, parameterId, recommendation, m_QueryStr, m_TypeQueryStr, m_CreateQueryStr, m_UpdateQueryStr, parent);

        parent->addWidget(form);

        return form;
    }

    return 0;
}

void ParameterValueWithType::acceptCreate(int recommendationFromId, QString fieldKey)
{
    if(form != 0) form->acceptCreate(recommendationFromId, fieldKey);
}

void ParameterValueWithType::acceptEdit()
{
    if(form != 0) form->acceptEdit();
}
