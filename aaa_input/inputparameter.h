#ifndef INPUTPARAMETER_H
#define INPUTPARAMETER_H

#include <QVariant>
#include <QDomDocument>

#include "parameterrecommendation.h"

class InputParameter
{
public:
    InputParameter(ParameterRecommendation* recommendation = 0);
    ~InputParameter();

    virtual void addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);
    virtual void loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    ParameterRecommendation* m_Recommendation;
};

#endif // INPUTPARAMETER_H
