#ifndef PREFLUSHFORM_H
#define PREFLUSHFORM_H

#include <QWidget>

namespace Ui {
class PreFlushForm;
}

class PreFlushForm : public QWidget
{
    Q_OBJECT

public:
    explicit PreFlushForm(QWidget *parent = 0);
    ~PreFlushForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::PreFlushForm *ui;
};

#endif // PREFLUSHFORM_H
