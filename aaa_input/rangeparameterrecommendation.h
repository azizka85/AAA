#ifndef RANGEPARAMETERRECOMMENDATION_H
#define RANGEPARAMETERRECOMMENDATION_H

#include "parameterrecommendation.h"

class RangeParameterRecommendation : public ParameterRecommendation
{
public:
    RangeParameterRecommendation(QString queryStr);

    void addRecommendationElement(int recommendationId, QVariant value, QDomElement &parameterElement, QDomDocument &document, QMap<QString, QVariant> &formData);
};

#endif // RANGEPARAMETERRECOMMENDATION_H
