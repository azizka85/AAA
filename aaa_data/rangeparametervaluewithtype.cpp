#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "rangeparametervaluewithtype.h"

RangeParameterValueWithType::RangeParameterValueWithType(double rangeMin, double rangeMax, int decimals,
                                            QString queryStr, QString typeIdQueryStr, QString typeQueryStr,
                                            QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr)
    : ParameterValue(queryStr, createQueryStr, updateQueryStr)
{
    m_RangeMin = rangeMin;
    m_RangeMax = rangeMax;

    m_Decimals = decimals;

    m_QueryStr = queryStr;

    m_TypeIdQueryStr = typeIdQueryStr;
    m_TypeQueryStr = typeQueryStr;

    m_CreateQueryStr = createQueryStr;
    m_CreateParameterQueryStr = createParameterQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_UpdateParameterQueryStr = updateParameterQueryStr;
}

RangeParameterValueWithType::~RangeParameterValueWithType()
{
    qDebug() << "RangeParameterValueWithType is destroyed";
}

QWidget *RangeParameterValueWithType::display(int id, int parameterId, QString recommendation, QVBoxLayout *parent)
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

        form = new RangeParameterValueWithTypeForm(m_RangeMin, m_RangeMax, m_Decimals, id, typeId, parameterId, recommendation, m_QueryStr, m_TypeQueryStr, m_CreateQueryStr, m_CreateParameterQueryStr, m_UpdateQueryStr, m_UpdateParameterQueryStr, parent);

        parent->addWidget(form);

        return form;
    }

    return 0;
}

void RangeParameterValueWithType::acceptCreate(int recommendationFromId, QString fieldKey)
{
    if(form != 0) form->acceptCreate(recommendationFromId, fieldKey);
}

void RangeParameterValueWithType::acceptEdit()
{
    if(form != 0) form->acceptEdit();
}
