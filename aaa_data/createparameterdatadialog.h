#ifndef CREATEPARAMETERDATADIALOG_H
#define CREATEPARAMETERDATADIALOG_H

#include <QDialog>

namespace Ui {
class CreateParameterDataDialog;
}

class CreateParameterDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateParameterDataDialog(QString boxCreateTitle, QString createQueryStr, QWidget *parent = 0);
    ~CreateParameterDataDialog();

public slots:
    void acceptCreateData();

private:
    Ui::CreateParameterDataDialog *ui;

    QString m_CreateQueryStr;
};

#endif // CREATEPARAMETERDATADIALOG_H
