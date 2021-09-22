#include <QDebug>

#include "parameterdatawithcategorymodel.h"

ParameterDataWithCategoryModel::ParameterDataWithCategoryModel(QObject *parent) : QIdentityProxyModel(parent)
{

}

ParameterDataWithCategoryModel::~ParameterDataWithCategoryModel()
{
    qDebug() << "ParameterDataWithCategory Model is destroyed";
}

QVariant ParameterDataWithCategoryModel::data(const QModelIndex &index, int role) const
{
    int rowIndex = index.row();
    int column = index.column();

    if(role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else if(role == Qt::BackgroundColorRole)
    {
        if(column == categoryColumn) return categoryMap[rowIndex];
        else return rowIndex % 2 == 0 ? QColor(220, 220, 220) : QColor("white");
    }    

    return QIdentityProxyModel::data(index, role);
}

Qt::ItemFlags ParameterDataWithCategoryModel::flags(const QModelIndex &index) const
{
    int column = index.column();

    if(categoryColumn == column)
    {
        return Qt::ItemIsEnabled;
    }

    return QIdentityProxyModel::flags(index);
}
