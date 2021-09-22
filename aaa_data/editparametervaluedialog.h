#ifndef EDITPARAMETERVALUEDIALOG_H
#define EDITPARAMETERVALUEDIALOG_H

#include <QDialog>

#include "parametervalue.h"

namespace Ui {
class EditParameterValueDialog;
}

class EditParameterValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditParameterValueDialog(int recommendationId, int parameterId, QString fieldKey, QString recommendation, QString propertyText, QString categoryText, QWidget *parent = 0);
    ~EditParameterValueDialog();

public slots:
    void acceptEdit();

private:
    Ui::EditParameterValueDialog *ui;

    int m_RecommendationId;
    int m_ParameterId;

    QString m_FieldKey;
};

#endif // EDITPARAMETERVALUEDIALOG_H
