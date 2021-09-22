#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "rangeparameterrecommendationwithcategory.h"

RangeParameterRecommendationWithCategory::RangeParameterRecommendationWithCategory(QString fieldKey, QString queryStr) : ParameterRecommendation(queryStr)
{
    m_FieldKey = fieldKey;
}

void RangeParameterRecommendationWithCategory::addRecommendationElement(int recommendationId, QVariant value, QDomElement &parameterElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QMap<QString, QVariant> data = formData[m_FieldKey].toMap();

    QVariant paramValue = data[value.toString()];

    qDebug() << "query: " << m_QueryStr << ", value: " << value << ", recommendationId: " << recommendationId << ", paramValue: " << paramValue;

    QSqlQuery query;

    query.prepare(m_QueryStr);
    query.addBindValue(paramValue);
    query.addBindValue(paramValue);
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
