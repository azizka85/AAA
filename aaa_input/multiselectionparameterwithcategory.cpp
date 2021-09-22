#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "multiselectionparameterwithcategory.h"

MultiSelectionParameterWithCategory::MultiSelectionParameterWithCategory(QString queryStr, ParameterRecommendation *recommendation)
    : InputParameter(recommendation)
{
    m_QueryStr = queryStr;
}

void MultiSelectionParameterWithCategory::addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
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

        int typeId = query.value(2).toInt();
        QString type = query.value(3).toString();

        QDomElement parameterElement = document.createElement("parameter");

        parameterElement.setAttribute("id", paramId);
        parameterElement.setAttribute("value", paramValue);
        parameterElement.setAttribute("typeId", typeId);
        parameterElement.setAttribute("type", type);

        if(m_Recommendation != 0) m_Recommendation->addRecommendationElement(recommendationId, paramId, parameterElement, document, formData);

        propertyElement.appendChild(parameterElement);
    }
}

void MultiSelectionParameterWithCategory::loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
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
