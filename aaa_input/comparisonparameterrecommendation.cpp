#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "comparisonparameterrecommendation.h"

ComparisonParameterRecommendation::ComparisonParameterRecommendation(QString fieldKey, QString criteriaQueryStr, QString queryStr) : ParameterRecommendation(queryStr)
{
    m_FieldKey = fieldKey;
    m_CriteriaQueryStr = criteriaQueryStr;
}

void ComparisonParameterRecommendation::addRecommendationElement(int recommendationId, QVariant value, QDomElement &parameterElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    if(!value.isNull() && !value.toString().isEmpty())
    {
        value = value.toString().toDouble();

        QStringList idList;

        QSqlQuery criteriaQuery;

        criteriaQuery.prepare(m_CriteriaQueryStr);
        criteriaQuery.addBindValue(recommendationId);

        bool criteriaQueryExecuted = criteriaQuery.exec();

        qDebug() << "Query executed: " << criteriaQueryExecuted;

        if(!criteriaQueryExecuted)
        {
            qDebug() << "Query execution error: " << criteriaQuery.lastError();
        }

        while(criteriaQuery.next())
        {
            QString compareFieldKey = criteriaQuery.value(1).toString();

            QVariant compareValue = formData[compareFieldKey];

            int criteria = criteriaQuery.value(2).toInt();

            switch(criteria)
            {
            case 0:

                if(compareValue.isNull() || compareValue.toString().isEmpty()) idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            case 1:

                if(!compareValue.isNull() && !compareValue.toString().isEmpty())  idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            case 2:

                if(!compareValue.isNull() && !compareValue.toString().isEmpty() && compareValue == value) idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            case 3:

                if(!compareValue.isNull() && !compareValue.toString().isEmpty() && compareValue != value) idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            case 4:

                if(!compareValue.isNull() && !compareValue.toString().isEmpty() && compareValue > value) idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            case 5:

                if(!compareValue.isNull() && !compareValue.toString().isEmpty() && compareValue >= value) idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            case 6:

                if(!compareValue.isNull() && !compareValue.toString().isEmpty() && compareValue < value) idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            case 7:

                if(!compareValue.isNull() && !compareValue.toString().isEmpty() && compareValue <= value) idList << QString::number(criteriaQuery.value(0).toInt());

                break;

            }
        }

        QSqlQuery query;

        QString queryStr = m_QueryStr.arg(idList.join(',')).arg(recommendationId);

        qDebug() << "queryStr: " << queryStr;

        query.prepare(queryStr);

        bool queryExecuted = query.exec();

        qDebug() << "Query executed: " << queryExecuted;

        if(!queryExecuted)
        {
            qDebug() << "Query execution error: " << query.lastError();
        }

        while(query.next())
        {
            QDomElement recommendationElement = document.createElement("recommendation");

            recommendationElement.setAttribute("id", query.value(0).toString());
            recommendationElement.setAttribute("parameterId", query.value(1).toString());
            recommendationElement.setAttribute("compareFieldKey", query.value(2).toString());
            recommendationElement.setAttribute("criteria", query.value(3).toString());

            QDomText textNode = document.createTextNode(query.value(4).toString());

            recommendationElement.appendChild(textNode);

            parameterElement.appendChild(recommendationElement);
        }
    }
}
