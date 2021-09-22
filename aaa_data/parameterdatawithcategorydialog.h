#ifndef PARAMETERDATAWITHCATEGORYDIALOG_H
#define PARAMETERDATAWITHCATEGORYDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QSqlQueryModel>

#include "parameterdatawithcategorymodel.h"

namespace Ui {
class ParameterDataWithCategoryDialog;
}

class ParameterDataWithCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterDataWithCategoryDialog(QString queryStr,
                                             QString selectQueryStr, QString createQueryStr, QString updateQueryStr, QString deleteQueryStr,
                                             QString categoryQueryStr,
                                             QString boxCreateTitle, QString boxUpdateTitle, QString boxDeleteTitle, QString boxDeleteQuestion,
                                             QString categoryHeaderData, QString nameHeaderData, QString descriptionHeaderData, QWidget *parent = 0);
    ~ParameterDataWithCategoryDialog();

public slots:
    void contextMenuRequested(const QPoint& pos);
    void contextMenuTriggered(QAction* action);

private:
    Ui::ParameterDataWithCategoryDialog *ui;

    QString m_QueryStr;

    QString m_SelectQueryStr;
    QString m_CreateQueryStr;
    QString m_UpdateQueryStr;
    QString m_DeleteQueryStr;

    QString m_CategoryQueryStr;

    QString m_BoxCreateTitle;
    QString m_BoxUpdateTitle;
    QString m_BoxDeleteTitle;
    QString m_BoxDeleteQuestion;

    QString m_CategoryHeaderData;
    QString m_NameHeaderData;
    QString m_DescriptionHeaderData;

    ParameterDataWithCategoryModel *model;
    QSqlQueryModel *queryModel;

    QMenu *tableViewContextMenu;

    QModelIndex currentIndex;

    void displayData();
    void tableViewDataBind(int categoryIdColumn, int categoryColumn);
};

#endif // PARAMETERDATAWITHCATEGORYDIALOG_H
