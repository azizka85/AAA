#ifndef MAPSELECTIONPARAMETER_H
#define MAPSELECTIONPARAMETER_H

#include "inputparameter.h"

class MapSelectionParameter : public InputParameter
{
public:
    MapSelectionParameter(QString queryStr, ParameterRecommendation* recommendation = 0);

    void addParameterElement(int recommendationId, QVariant value, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);
    void loadDataFromElement(QString key, QDomElement &propertyElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    QString m_QueryStr;
};

#endif // MAPSELECTIONPARAMETER_H
