#ifndef RANGEPARAMETERVALUEFORM_H
#define RANGEPARAMETERVALUEFORM_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class RangeParameterValueForm;
}

class RangeParameterValueForm : public QWidget
{
    Q_OBJECT

public:
    explicit RangeParameterValueForm(double rangeMin, double rangeMax, int decimals, int id, int parameterId, QString recommendation, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr, QVBoxLayout *parent);
    ~RangeParameterValueForm();

    void display();

    void acceptCreate(int recommendationFromId, QString fieldKey);

    void acceptEdit();

private:
    Ui::RangeParameterValueForm *ui;

    int m_Id;

    int m_ParameterId;

    QString m_QueryStr;
    QString m_CreateQueryStr;
    QString m_CreateParameterQueryStr;
    QString m_UpdateQueryStr;
    QString m_UpdateParameterQueryStr;

    void dataBind();
};

#endif // RANGEPARAMETERVALUEFORM_H
