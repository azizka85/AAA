#include <QDebug>

#include "updatemodel.h"

UpdateModel::UpdateModel(int idColumn, int column, QObject *parent) : QSqlQueryModel(parent)
{
    m_IdColumn = idColumn;

    m_Column = column;
}

UpdateModel::~UpdateModel()
{
    qDebug() << "UpdateModel is destroyed";
}

Qt::ItemFlags UpdateModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags pFlags = QSqlQueryModel::flags(index);

    if(index.isValid() && index.column() == m_Column)
    {
        pFlags |= Qt::ItemIsEditable;
    }

    return pFlags;
}

QVariant UpdateModel::data(const QModelIndex &item, int role) const
{
    if(item.isValid() && item.column() == m_Column && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        int id = index(item.row(), m_IdColumn).data().toInt();

        if(uData.contains(id)) return uData[id];
    }

    return QSqlQueryModel::data(item, role);
}

bool UpdateModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && index.column() == m_Column && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        int id = this->index(index.row(), m_IdColumn).data().toInt();

        if(!value.isNull() && !value.toString().isEmpty()) uData[id] = value;
        else uData.remove(id);

        return true;
    }

    return QSqlQueryModel::setData(index, value, role);
}

QMap<QString, QVariant> UpdateModel::updateData()
{
    QMap<QString, QVariant> data;

    for(int i = 0; i < uData.keys().length(); i++)
    {
        QString key = QString::number(uData.keys().at(i));

        QVariant value = uData.values().at(i);

        data[key] = value;
    }

    return data;
}

void UpdateModel::setUpdateData(QMap<QString, QVariant> data)
{
    for(int i = 0; i < data.keys().length(); i++)
    {
        int key = data.keys().at(i).toInt();

        QVariant value = data.values().at(i);

        uData[key] = value;
    }
}
