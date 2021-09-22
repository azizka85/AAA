#ifndef CALCULATIONDATAFORM_H
#define CALCULATIONDATAFORM_H

#include <QWidget>

namespace Ui {
class CalculationDataForm;
}

class CalculationDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit CalculationDataForm(QWidget *parent = 0);
    ~CalculationDataForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

public slots:
    void textEdited();

private:
    Ui::CalculationDataForm *ui;

    double L;
    double minID;
    double q;
    double mu;
    double H;
    double Pfrac;
    double Pres;
    double K;
    double B;
    double Re;
    double Rw;
    double Rd;
    double Vtbg;
    double S;

    void calculate();
    void dataBind(QMap<QString, QVariant> &formData);
};

#endif // CALCULATIONDATAFORM_H
