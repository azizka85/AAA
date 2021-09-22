#include <QDebug>

#include "editparametervaluedialog.h"
#include "ui_editparametervaluedialog.h"

#include "settings.h"

EditParameterValueDialog::EditParameterValueDialog(int recommendationId, int parameterId, QString fieldKey, QString recommendation, QString propertyText, QString categoryText, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditParameterValueDialog)
{
    ui->setupUi(this);

    m_RecommendationId = recommendationId;
    m_ParameterId = parameterId;

    ui->propertyText->setText(propertyText);
    ui->categoryText->setText(categoryText);

    m_FieldKey = fieldKey;

    if(Settings::get()->formMap.contains(m_FieldKey)) Settings::get()->formMap[m_FieldKey]->display(recommendationId, parameterId, recommendation, ui->verticalLayout);
}

EditParameterValueDialog::~EditParameterValueDialog()
{
    delete ui;

    qDebug() << "EditParameterValue Dialog is destroyed";
}

void EditParameterValueDialog::acceptEdit()
{
    if(Settings::get()->formMap.contains(m_FieldKey)) Settings::get()->formMap[m_FieldKey]->acceptEdit();

    accept();
}
