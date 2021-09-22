#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "mapselectionparameter.h"

MapSelectionParameter::MapSelectionParameter(QString queryStr, ParameterRecommendation *recommendation) : InputParameter(recommendation)
{
    m_QueryStr = queryStr;
}

void MapSelectionParameter::addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QMap<QString, QVariant> data = value.toMap();

    QSqlQuery query;

    QString queryStr = m_QueryStr.arg(data.keys().join(','));

    query.prepare(queryStr);

    bool queryExecuted = query.exec();

    qDebug() << "Query executed: " << queryExecuted;

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    while(query.next())
    {
        QString paramId = query.value(0).toString();
        QString paramName = query.value(1).toString();
        QString paramValue = data[paramId].toString();

        QDomElement parameterElement = document.createElement("parameter");

        parameterElement.setAttribute("id", paramId);
        parameterElement.setAttribute("value", paramValue);
        parameterElement.setAttribute("name", paramName);

        if(m_Recommendation != 0) m_Recommendation->addRecommendationElement(recommendationId, paramId, parameterElement, document, formData);

        propertyElement.appendChild(parameterElement);
    }
}

void MapSelectionParameter::loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QDomNodeList nodeList = propertyElement.childNodes();

    int count = nodeList.count();

    QMap<QString, QVariant> data;

    for(int i = 0; i < count; i++)
    {
        QDomNode node = nodeList.at(i);

        if(node.isElement())
        {
            QDomElement childElement = node.toElement();

            QString id = childElement.attribute("id");
            QString value = childElement.attribute("value");

            if(!id.isEmpty() && !value.isEmpty()) data[id] = value;
        }
    }

    formData[key] = data;
}
