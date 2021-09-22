#ifndef CREATEPARAMETERDATAWITHCATEGORYDIALOG_H
#define CREATEPARAMETERDATAWITHCATEGORYDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class CreateParameterDataWithCategoryDialog;
}

class CreateParameterDataWithCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateParameterDataWithCategoryDialog(QString boxCreateTitle, QString createQueryStr, QString categoryQueryStr,
                                                   QString categoryHeaderData, QString nameHeaderData, QString descriptionHeaderData, QWidget *parent = 0);
    ~CreateParameterDataWithCategoryDialog();

public slots:
    void acceptCreateData();

private:
    Ui::CreateParameterDataWithCategoryDialog *ui;

    QString m_CreateQueryStr;
    QString m_CategoryQueryStr;

    QSqlQueryModel *categoryModel;

    void displayCategoryList();
};

#endif // CREATEPARAMETERDATAWITHCATEGORYDIALOG_H
