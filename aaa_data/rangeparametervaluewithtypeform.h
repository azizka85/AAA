#ifndef RANGEPARAMETERVALUEWITHTYPEFORM_H
#define RANGEPARAMETERVALUEWITHTYPEFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSqlQueryModel>

namespace Ui {
class RangeParameterValueWithTypeForm;
}

class RangeParameterValueWithTypeForm : public QWidget
{
    Q_OBJECT

public:
    explicit RangeParameterValueWithTypeForm(double rangeMin, double rangeMax, int decimals, int id, int typeId, int parameterId, QString recommendation,
                QString queryStr, QString typeQueryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr, QVBoxLayout *parent = 0);
    ~RangeParameterValueWithTypeForm();

    void display();

    void acceptCreate(int recommendationFromId, QString fieldKey);

    void acceptEdit();

public slots:

    void currentIndexChanged(int index);

private:
    Ui::RangeParameterValueWithTypeForm *ui;

    int m_Id;
    int m_TypeId;
    int m_ParameterId;

    QString m_QueryStr;
    QString m_TypeQueryStr;
    QString m_CreateQueryStr;
    QString m_CreateParameterQueryStr;
    QString m_UpdateQueryStr;
    QString m_UpdateParameterQueryStr;

    QSqlQueryModel *typeModel;

    void dataBind();
    void dataBindTypeId();
};

#endif // RANGEPARAMETERVALUEWITHTYPEFORM_H
