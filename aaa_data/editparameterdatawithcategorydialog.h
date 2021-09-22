#ifndef EDITPARAMETERDATAWITHCATEGORYDIALOG_H
#define EDITPARAMETERDATAWITHCATEGORYDIALOG_H

#include <QSqlQueryModel>
#include <QDialog>

namespace Ui {
class EditParameterDataWithCategoryDialog;
}

class EditParameterDataWithCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditParameterDataWithCategoryDialog(int id, int categoryId, QString selectQueryStr, QString updateQueryStr, QString categoryQueryStr,
                QString boxEditTitle, QString categoryHeaderData, QString nameHeaderData, QString descriptionHeaderData, QWidget *parent = 0);

    ~EditParameterDataWithCategoryDialog();

public slots:
    void acceptedEditData();

private:
    Ui::EditParameterDataWithCategoryDialog *ui;

    int m_Id;
    int m_CategoryId;

    QString m_SelectQueryStr;
    QString m_UpdateQueryStr;
    QString m_CategoryQueryStr;

    QSqlQueryModel *categoryModel;

    void displayData();
    void categoryDataBind();
};

#endif // EDITPARAMETERDATAWITHCATEGORYDIALOG_H
