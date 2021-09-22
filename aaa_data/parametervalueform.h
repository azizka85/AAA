#ifndef PARAMETERVALUEFORM_H
#define PARAMETERVALUEFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSqlQueryModel>

namespace Ui {
class ParameterValueForm;
}

class ParameterValueForm : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterValueForm(int id, int parameterId, QString recommendation, QString queryStr, QString createQueryStr, QString updateQueryStr, QVBoxLayout *parent);
    ~ParameterValueForm();

    void display();

    void acceptCreate(int recommendationFromId, QString fieldKey);

    void acceptEdit();

public slots:

    void currentIndexChanged(int index);

private:
    Ui::ParameterValueForm *ui;

    QSqlQueryModel *model;

    int m_Id;

    int m_ParameterId;

    QString m_QueryStr;
    QString m_CreateQueryStr;
    QString m_UpdateQueryStr;

    void dataBind();
};

#endif // PARAMETERVALUEFORM_H
