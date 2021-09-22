#ifndef WELLDATAFORM_H
#define WELLDATAFORM_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class WellDataForm;
}

class WellDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit WellDataForm(QWidget *parent = 0);
    ~WellDataForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

public slots:
    void textEdited();

private:
    Ui::WellDataForm *ui;

    double Vtbg;
    double Lpz;

    QSqlQueryModel* wellTypeModel;
    QSqlQueryModel* deviationModel;
    QSqlQueryModel* completionTypeModel;
    QSqlQueryModel* holeTypeModel;

    void wellTypeDataBind(int id);
    void deviationDataBind(int id);
    void completionDataBind(int id);
    void holeTypeDataBind(int id);

    void calculate();
};

#endif // WELLDATAFORM_H
