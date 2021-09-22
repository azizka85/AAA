#ifndef DATAITEM_H
#define DATAITEM_H

#include <QString>
#include <QSqlQuery>

class ParameterData
{
public:
    ParameterData(QString queryStr);

    virtual QString text(int parameterId) const;

    ~ParameterData();

protected:
    QString m_QueryStr;

    QSqlQuery execQuery(int parameterId) const;
};

#endif // DATAITEM_H
