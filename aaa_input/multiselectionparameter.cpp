#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "multiselectionparameter.h"

MultiSelectionParameter::MultiSelectionParameter(QString queryStr, ParameterRecommendation *recommendation)
    : InputParameter(recommendation)
{
    m_QueryStr = queryStr;
}

void MultiSelectionParameter::addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QSqlQuery query;

    QString queryStr = m_QueryStr.arg(value.toStringList().join(','));

    query.prepare(queryStr);

    bool queryExecuted = query.exec();

    qDebug() << "Query executed: " << queryExecuted;

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    while(query.next())
    {
        int paramId = query.value(0).toInt();
        QString paramValue = query.value(1).toString();

        QDomElement parameterElement = document.createElement("parameter");

        parameterElement.setAttribute("id", paramId);
        parameterElement.setAttribute("value", paramValue);

        if(m_Recommendation != 0) m_Recommendation->addRecommendationElement(recommendationId, paramId, parameterElement, document, formData);

        propertyElement.appendChild(parameterElement);
    }
}

void MultiSelectionParameter::loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QDomNodeList nodeList = propertyElement.childNodes();

    int count = nodeList.count();

    QList<QVariant> idList;

    for(int i = 0; i < count; i++)
    {
        QDomNode node = nodeList.at(i);

        if(node.isElement())
        {
            QDomElement childElement = node.toElement();

            QString id = childElement.attribute("id");

            if(!id.isEmpty()) idList << id;
        }
    }

    formData[key] = idList;
}
