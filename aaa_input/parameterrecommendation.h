#ifndef PARAMETERRECOMMENDATION_H
#define PARAMETERRECOMMENDATION_H

#include <QVariant>
#include <QString>
#include <QDomDocument>

class ParameterRecommendation
{
public:
    ParameterRecommendation(QString queryStr);
    ~ParameterRecommendation();

    virtual void addRecommendationElement(int recommendationId, QVariant value, QDomElement &parameterElement, QDomDocument &document, QMap<QString, QVariant> &formData);

protected:
    QString m_QueryStr;
};

#endif // PARAMETERRECOMMENDATION_H
