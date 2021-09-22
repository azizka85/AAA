#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "comparisonparametervalue.h"

ComparisonParameterValue::ComparisonParameterValue(QString compareFieldQueryStr, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr)
    : ParameterValue(queryStr, createQueryStr, updateQueryStr)
{
    m_CompareFieldQueryStr = compareFieldQueryStr;
    m_QueryStr = queryStr;
    m_CreateQueryStr = createQueryStr;
    m_CreateParameterQueryStr = createParameterQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_UpdateParameterQueryStr = updateParameterQueryStr;

    form = 0;
}

ComparisonParameterValue::~ComparisonParameterValue()
{
    qDebug() << "ComparisonParameterValue is destroyed";
}

QWidget *ComparisonParameterValue::display(int id, int parameterId, QString recommendation, QVBoxLayout *parent)
{
    if(parent != 0)
    {
        int fieldId = -1;
        int criteriaId = -1;

        if(parameterId >= 0)
        {
            QSqlQuery query;

            query.prepare(m_CompareFieldQueryStr);
            query.addBindValue(parameterId);

            bool queryExecuted = query.exec();

            qDebug() << "Query executed: " << queryExecuted;

            if(!queryExecuted)
            {
                qDebug() << "Query execution error: " << query.lastError();
            }

            while(query.next())
            {
                fieldId = query.value(0).toInt();
                criteriaId = query.value(1).toInt();
            }
        }

        form = new ComparisonParameterValueForm(id, fieldId, criteriaId, parameterId, recommendation, m_QueryStr, m_CreateQueryStr, m_CreateParameterQueryStr, m_UpdateQueryStr, m_UpdateParameterQueryStr, parent);

        parent->addWidget(form);

        return form;
    }

    return 0;
}

void ComparisonParameterValue::acceptCreate(int recommendationFromId, QString fieldKey)
{
    if(form != 0) form->acceptCreate(recommendationFromId, fieldKey);
}

void ComparisonParameterValue::acceptEdit()
{
    if(form != 0) form->acceptEdit();
}
