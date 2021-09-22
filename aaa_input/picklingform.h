#ifndef PICKLINGFORM_H
#define PICKLINGFORM_H

#include <QWidget>
#include <QSqlQueryModel>

#include "updatemodel.h"

#include "doubleeditordelegate.h"

namespace Ui {
class PicklingForm;
}

class PicklingForm : public QWidget
{
    Q_OBJECT

public:
    explicit PicklingForm(QWidget *parent = 0);
    ~PicklingForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::PicklingForm *ui;

    UpdateModel* additivesModel;

    DoubleEditorDelegate* doubleDelegate;
};

#endif // PICKLINGFORM_H
