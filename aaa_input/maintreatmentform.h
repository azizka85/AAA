#ifndef MAINTREATMENTFORM_H
#define MAINTREATMENTFORM_H

#include <QWidget>
#include <QSqlQueryModel>

#include "updatemodel.h"

#include "doubleeditordelegate.h"

namespace Ui {
class MainTreatmentForm;
}

class MainTreatmentForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainTreatmentForm(QWidget *parent = 0);
    ~MainTreatmentForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::MainTreatmentForm *ui;

    UpdateModel* additivesModel;

    DoubleEditorDelegate *doubleDelegate;
};

#endif // MAINTREATMENTFORM_H
