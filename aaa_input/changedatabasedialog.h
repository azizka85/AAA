#ifndef CHANGEDATABASEDIALOG_H
#define CHANGEDATABASEDIALOG_H

#include <QString>
#include <QDialog>

namespace Ui {
class ChangeDatabaseDialog;
}

class ChangeDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDatabaseDialog(QWidget *parent = 0);
    ~ChangeDatabaseDialog();

public slots:
    void databasePathButtonClicked();

private:
    Ui::ChangeDatabaseDialog *ui;

    void displayStatus(QString fileName);
};

#endif // CHANGEDATABASEDIALOG_H
