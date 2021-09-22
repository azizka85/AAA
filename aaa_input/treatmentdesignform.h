#ifndef TREATMENTDESIGNFORM_H
#define TREATMENTDESIGNFORM_H

#include <QWidget>

namespace Ui {
class TreatmentDesignForm;
}

class TreatmentDesignForm : public QWidget
{
    Q_OBJECT

public:
    explicit TreatmentDesignForm(QWidget *parent = 0);
    ~TreatmentDesignForm();

    void display(QMap<QString, QString>& formMap, QMap<QString, QVariant> &formData);
    void saveFormData(QMap<QString, QVariant> &formData);

private:
    Ui::TreatmentDesignForm *ui;
};

#endif // TREATMENTDESIGNFORM_H
