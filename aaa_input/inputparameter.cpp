#include <QDebug>

#include "inputparameter.h"

InputParameter::InputParameter(ParameterRecommendation *recommendation)
{
    m_Recommendation = recommendation;
}

InputParameter::~InputParameter()
{
    qDebug() << "InputParameter is destroyed";

    delete m_Recommendation;
}

void InputParameter::addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QDomElement parameterElement = document.createElement("parameter");

    parameterElement.setAttribute("value", value.toString());

    if(m_Recommendation != 0) m_Recommendation->addRecommendationElement(recommendationId, value, parameterElement, document, formData);

    propertyElement.appendChild(parameterElement);
}

void InputParameter::loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData)
{
    QDomElement childElement = propertyElement.firstChildElement();

    if(!childElement.isNull())
    {
        QString value = childElement.attribute("value");

        if(!value.isEmpty()) formData[key] = value;
    }
}
