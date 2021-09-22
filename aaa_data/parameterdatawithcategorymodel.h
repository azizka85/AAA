#ifndef PARAMETERDATAWITHCATEGORYMODEL_H
#define PARAMETERDATAWITHCATEGORYMODEL_H

#include <QObject>
#include <QVariant>
#include <QColor>
#include <QMap>
#include <QIdentityProxyModel>

class ParameterDataWithCategoryModel : public QIdentityProxyModel
{
public:
    ParameterDataWithCategoryModel(QObject* parent);
    ~ParameterDataWithCategoryModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QMap<int, QColor> categoryMap;

    int categoryColumn;
};

#endif // PARAMETERDATAWITHCATEGORYMODEL_H
