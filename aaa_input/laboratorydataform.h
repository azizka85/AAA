#ifndef LABORATORYDATAFORM_H
#define LABORATORYDATAFORM_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class LaboratoryDataForm;
}

class LaboratoryDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit LaboratoryDataForm(QWidget *parent = 0);
    ~LaboratoryDataForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::LaboratoryDataForm *ui;

    QSqlQueryModel* compatibilityDataModel;

    void compatibilityDataBind(QList<QVariant> compatibilityDataIdList);
};

#endif // LABORATORYDATAFORM_H
