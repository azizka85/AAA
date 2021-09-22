#ifndef MULTISELECTIONPARAMETERWITHCATEGORY_H
#define MULTISELECTIONPARAMETERWITHCATEGORY_H

#include "inputparameter.h"

class MultiSelectionParameterWithCategory : public InputParameter
{
public:
    MultiSelectionParameterWithCategory(QString queryStr, ParameterRecommendation* recommendation = 0);

    void addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);
    void loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    QString m_QueryStr;
};

#endif // MULTISELECTIONPARAMETERWITHCATEGORY_H
