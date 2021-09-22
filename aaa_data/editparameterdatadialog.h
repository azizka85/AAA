#ifndef EDITPARAMETERDATADIALOG_H
#define EDITPARAMETERDATADIALOG_H

#include <QDialog>

namespace Ui {
class EditParameterDataDialog;
}

class EditParameterDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditParameterDataDialog(int id, QString selectQueryStr, QString updateQueryStr, QString boxEditTitle, QWidget *parent = 0);
    ~EditParameterDataDialog();

public slots:
    void acceptedEditData();

private:
    Ui::EditParameterDataDialog *ui;

    int m_Id;

    QString m_SelectQueryStr;
    QString m_UpdateQueryStr;

    void displayData();
};

#endif // EDITPARAMETERDATADIALOG_H
