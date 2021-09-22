#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "rangeparameterrecommendation.h"

RangeParameterRecommendation::RangeParameterRecommendation(QString queryStr) : ParameterRecommendation(queryStr)
{

}

void RangeParameterRecommendation::addRecommendationElement(int recommendationId, QVariant value, QDomElement &parameterElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    if(!value.isNull() && !value.toString().isEmpty())
    {
        qDebug() << "query: " << m_QueryStr << ", value: " << value << "recommendationId: " << recommendationId;

        QSqlQuery query;

        query.prepare(m_QueryStr);
        query.addBindValue(value);
        query.addBindValue(value);
        query.addBindValue(recommendationId);

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
            recommendationElement.setAttribute("min", query.value(2).toString());
            recommendationElement.setAttribute("max", query.value(3).toString());

            QDomText textNode = document.createTextNode(query.value(4).toString());

            recommendationElement.appendChild(textNode);

            parameterElement.appendChild(recommendationElement);
        }
    }
}

