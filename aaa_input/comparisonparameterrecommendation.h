#ifndef COMPARISONPARAMETERRECOMMENDATION_H
#define COMPARISONPARAMETERRECOMMENDATION_H

#include "parameterrecommendation.h"

class ComparisonParameterRecommendation : public ParameterRecommendation
{
public:
    ComparisonParameterRecommendation(QString fieldKey, QString criteriaQueryStr, QString queryStr);

    void addRecommendationElement(int recommendationId, QVariant value, QDomElement &parameterElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    QString m_FieldKey;
    QString m_CriteriaQueryStr;
};

#endif // COMPARISONPARAMETERRECOMMENDATION_H
