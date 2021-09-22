#ifndef COMPARISONPARAMETERVALUEFORM_H
#define COMPARISONPARAMETERVALUEFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QStringListModel>

namespace Ui {
class ComparisonParameterValueForm;
}

class ComparisonParameterValueForm : public QWidget
{
    Q_OBJECT

public:
    explicit ComparisonParameterValueForm(int id, int fieldId, int criteriaId, int parameterId, QString recommendation, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr, QVBoxLayout *parent = 0);
    ~ComparisonParameterValueForm();

    void acceptCreate(int recommendationFromId, QString fieldKey);

    void acceptEdit();

private:
    Ui::ComparisonParameterValueForm *ui;

    QSqlQueryModel *model;
    QStringListModel *criteriaModel;

    int m_Id;
    int m_FieldId;
    int m_CriteriaId;
    int m_ParameterId;

    QString m_QueryStr;
    QString m_CreateQueryStr;
    QString m_CreateParameterQueryStr;
    QString m_UpdateQueryStr;
    QString m_UpdateParameterQueryStr;

    void displayFieldList();

    void criteriaDataBind();
    void fieldDataBind();
};

#endif // COMPARISONPARAMETERVALUEFORM_H
