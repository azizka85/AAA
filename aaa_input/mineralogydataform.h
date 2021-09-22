#ifndef MINERALOGYDATAFORM_H
#define MINERALOGYDATAFORM_H

#include <QWidget>
#include <QSqlQueryModel>

#include "parameterdatawithcategorymodel.h"

namespace Ui {
class MineralogyDataForm;
}

class MineralogyDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit MineralogyDataForm(QWidget *parent = 0);
    ~MineralogyDataForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);

    void saveFormData(QMap<QString, QVariant>& formData);

private:
    Ui::MineralogyDataForm *ui;    

    QSqlQueryModel* formationTypeModel;

    QSqlQueryModel* clayTypeModel;

    QSqlQueryModel* formationDamageQueryModel;

    ParameterDataWithCategoryModel* formationDamageModel;

    void tableViewDataBind(int categoryIdColumn, int categoryColumn);

    void formationTypeDataBind(int id);
    int formationTypeSaveData();

    void clayTypeDataBind(int id);
    int clayTypeSaveData();

    void formationDamageDataBind(QList<QVariant> idList);
    QList<QVariant> formationDamageSaveData();
};

#endif // MINERALOGYDATAFORM_H
