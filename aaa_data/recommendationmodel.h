#ifndef RECOMMENDATIONMODEL_H
#define RECOMMENDATIONMODEL_H

#include <QMap>
#include <QIdentityProxyModel>

#include "parameterdata.h"

class RecommendationModel : public QIdentityProxyModel
{
public:
    RecommendationModel(QObject* parent);
    ~RecommendationModel();

    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

    QMap<int, QColor> categoryMap;
    QMap<int, QColor> fieldMap;

    QMap<QString, ParameterData*> parameterDataMap;

    int categoryColumn;
    int fieldColumn;
    int fieldKeyColumn;
    int parameterIdColumn;
};

#endif // RECOMMENDATIONMODEL_H
