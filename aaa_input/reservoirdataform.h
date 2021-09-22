#ifndef RESERVOIRDATAFORM_H
#define RESERVOIRDATAFORM_H

#include <QList>
#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class ReservoirDataForm;
}

class ReservoirDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReservoirDataForm(QWidget *parent = 0);
    ~ReservoirDataForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData);

    virtual void saveFormData(QMap<QString, QVariant>& formData);

public slots:
    void textEdited();

private:
    Ui::ReservoirDataForm *ui;

    double Kd;
    double Rd;
    double Rw;

    QSqlQueryModel* reservoirTypeModel;
    QSqlQueryModel* driveMechanismModel;

    void reservoirTypeDataBind(QList<QVariant> idList);
    QList<QVariant> reservoirTypeSaveData();

    void driveMechanismDataBind(QList<QVariant> idList);
    QList<QVariant> driveMechanismSaveData();

    void calculate();
};

#endif // RESERVOIRDATAFORM_H
