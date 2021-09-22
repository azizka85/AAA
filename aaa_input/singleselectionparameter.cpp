#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "singleselectionparameter.h"

SingleSelectionParameter::SingleSelectionParameter(QString queryStr, ParameterRecommendation *recommendation) : InputParameter(recommendation)
{
    m_QueryStr = queryStr;
}

void SingleSelectionParameter::addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QSqlQuery query;

    query.prepare(m_QueryStr);
    query.addBindValue(value);

    bool queryExecuted = query.exec();

    qDebug() << "Query executed: " << queryExecuted;

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    QString paramValue = "";

    while(query.next())
    {
        paramValue = query.value(0).toString();
    }

    QDomElement parameterElement = document.createElement("parameter");

    parameterElement.setAttribute("id", value.toString());
    parameterElement.setAttribute("value", paramValue);

    if(m_Recommendation != 0) m_Recommendation->addRecommendationElement(recommendationId, value, parameterElement, document, formData);

    propertyElement.appendChild(parameterElement);
}

void SingleSelectionParameter::loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QDomElement childElement = propertyElement.firstChildElement();

    if(!childElement.isNull())
    {
        QString id = childElement.attribute("id");

        if(!id.isEmpty()) formData[key] = id;
    }
}

