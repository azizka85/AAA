#ifndef PARAMETERVALUEWITHTYPEFORM_H
#define PARAMETERVALUEWITHTYPEFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSqlQueryModel>

namespace Ui {
class ParameterValueWithTypeForm;
}

class ParameterValueWithTypeForm : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterValueWithTypeForm(int id, int typeId, int parameterId, QString recommendation, QString queryStr, QString typeQueryStr, QString createQueryStr, QString updateQueryStr, QVBoxLayout *parent = 0);
    ~ParameterValueWithTypeForm();

    void display();

    void acceptCreate(int recommendationFromId, QString fieldKey);

    void acceptEdit();

public slots:

    void currentIndexChanged(int index);
    void currentTypeIndexChanged(int index);

private:
    Ui::ParameterValueWithTypeForm *ui;

    QSqlQueryModel *model;
    QSqlQueryModel *typeModel;

    int m_Id;
    int m_TypeId;
    int m_ParameterId;

    QString m_QueryStr;
    QString m_TypeQueryStr;
    QString m_CreateQueryStr;
    QString m_UpdateQueryStr;

    void displayParameterList();

    void dataBindTypeId();
    void dataBindParameterId();
};

#endif // PARAMETERVALUEWITHTYPEFORM_H
