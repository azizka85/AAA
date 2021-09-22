#ifndef STFBFORM_H
#define STFBFORM_H

#include <QWidget>

namespace Ui {
class STFBForm;
}

class STFBForm : public QWidget
{
    Q_OBJECT

public:
    explicit STFBForm(QWidget *parent = 0);
    ~STFBForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::STFBForm *ui;
};

#endif // STFBFORM_H
