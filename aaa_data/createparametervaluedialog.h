#ifndef CREATEPARAMETERVALUEDIALOG_H
#define CREATEPARAMETERVALUEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QSqlQueryModel>

#include "parametervalue.h"

namespace Ui {
class CreateParameterValueDialog;
}

class CreateParameterValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateParameterValueDialog(int recommendationFromId, int fieldId, int categoryId, int parameterId, QString fieldKey, QWidget *parent = 0);
    ~CreateParameterValueDialog();

public slots:
    void acceptCreate();
    void currentIndexChanged(int index);
    void currentCategoryIndexChanged(int index);

private:
    Ui::CreateParameterValueDialog *ui;

    int m_RecommendationFromId;

    int m_FieldId;
    int m_CategoryId;
    int m_ParameterId;

    QString m_FieldKey;

    QSqlQueryModel *model;
    QSqlQueryModel *categoryModel;

    QWidget* currentWidget;

    void displayList();
    void displayCategoryList();

    void listDataBind();
    void categoryListDataBind();
};

#endif // CREATEPARAMETERVALUEDIALOG_H
