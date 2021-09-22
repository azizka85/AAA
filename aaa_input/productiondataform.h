#ifndef PRODUCTIONDATAFORM_H
#define PRODUCTIONDATAFORM_H

#include <QWidget>

namespace Ui {
class ProductionDataForm;
}

class ProductionDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductionDataForm(QWidget *parent = 0);
    ~ProductionDataForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::ProductionDataForm *ui;
};

#endif // PRODUCTIONDATAFORM_H
