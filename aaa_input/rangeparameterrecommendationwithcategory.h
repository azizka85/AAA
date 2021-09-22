#ifndef RANGEPARAMETERRECOMMENDATIONWITHCATEGORY_H
#define RANGEPARAMETERRECOMMENDATIONWITHCATEGORY_H

#include "parameterrecommendation.h"

class RangeParameterRecommendationWithCategory : public ParameterRecommendation
{
public:
    RangeParameterRecommendationWithCategory(QString fieldKey, QString queryStr);

    void addRecommendationElement(int recommendationId, QVariant value, QDomElement &parameterElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    QString m_FieldKey;
};

#endif // RANGEPARAMETERRECOMMENDATIONWITHCATEGORY_H
