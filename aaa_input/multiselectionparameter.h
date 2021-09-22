#ifndef MULTISELECTIONPARAMETER_H
#define MULTISELECTIONPARAMETER_H

#include "inputparameter.h"

class MultiSelectionParameter : public InputParameter
{
public:
    MultiSelectionParameter(QString queryStr, ParameterRecommendation* recommendation = 0);

    void addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);
    void loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    QString m_QueryStr;
};

#endif // MULTISELECTIONPARAMETER_H
