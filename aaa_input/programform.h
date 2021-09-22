#ifndef PROGRAMFORM_H
#define PROGRAMFORM_H

#include <QWidget>

namespace Ui {
class ProgramForm;
}

class ProgramForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramForm(QWidget *parent = 0);
    ~ProgramForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::ProgramForm *ui;
};

#endif // PROGRAMFORM_H
