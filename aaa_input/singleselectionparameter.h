#ifndef SINGLESELECTIONPARAMETER_H
#define SINGLESELECTIONPARAMETER_H

#include "inputparameter.h"

class SingleSelectionParameter : public InputParameter
{
public:
    SingleSelectionParameter(QString queryStr, ParameterRecommendation* recommendation = 0);

    void addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);
    void loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    QString m_QueryStr;
};

#endif // SINGLESELECTIONPARAMETER_H
