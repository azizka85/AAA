#ifndef OVERFLUSHFORM_H
#define OVERFLUSHFORM_H

#include <QWidget>

namespace Ui {
class OverFlushForm;
}

class OverFlushForm : public QWidget
{
    Q_OBJECT

public:
    explicit OverFlushForm(QWidget *parent = 0);
    ~OverFlushForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::OverFlushForm *ui;
};

#endif // OVERFLUSHFORM_H
