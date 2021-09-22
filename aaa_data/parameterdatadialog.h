#ifndef PARAMETERDATADIALOG_H
#define PARAMETERDATADIALOG_H

#include <QDialog>
#include <QMenu>
#include <QSqlQueryModel>

namespace Ui {
class ParameterDataDialog;
}

class ParameterDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterDataDialog(QString queryStr, QString selectQueryStr, QString createQueryStr, QString updateQueryStr, QString deleteQueryStr,
                                 QString boxCreateTitle, QString boxUpdateTitle, QString boxDeleteTitle, QString boxDeleteQuestion, QWidget *parent = 0);
    ~ParameterDataDialog();

public slots:
    void contextMenuRequested(const QPoint& pos);
    void contextMenuTriggered(QAction* action);

private:

    Ui::ParameterDataDialog *ui;

    QString m_QueryStr;
    QString m_SelectQueryStr;
    QString m_CreateQueryStr;
    QString m_UpdateQueryStr;
    QString m_DeleteQueryStr;

    QString m_BoxCreateTitle;
    QString m_BoxUpdateTitle;
    QString m_BoxDeleteTitle;
    QString m_BoxDeleteQuestion;

    QSqlQueryModel *model;

    QMenu *tableViewContextMenu;

    QModelIndex currentIndex;

    void displayData();
};

#endif // PARAMETERDATADIALOG_H
