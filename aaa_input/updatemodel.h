#ifndef UPDATEMODEL_H
#define UPDATEMODEL_H

#include <QSqlQueryModel>

class UpdateModel : public QSqlQueryModel
{
public:    

    UpdateModel(int idColumn, int column, QObject* parent);
    ~UpdateModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant data(const QModelIndex &item, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QMap<QString, QVariant> updateData();

    void setUpdateData(QMap<QString, QVariant> data);

private:
    int m_IdColumn;
    int m_Column;

    QMap<int, QVariant> uData;
};

#endif // UPDATEMODEL_H
