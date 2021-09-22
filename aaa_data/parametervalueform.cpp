#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "settings.h"

#include "parametervalueform.h"
#include "ui_parametervalueform.h"

ParameterValueForm::ParameterValueForm(int id, int parameterId, QString recommendation, QString queryStr, QString createQueryStr, QString updateQueryStr, QVBoxLayout *parent) :
    QWidget(parent->widget()),
    ui(new Ui::ParameterValueForm)
{
    ui->setupUi(this);

    m_Id = id;

    m_ParameterId = parameterId;

    m_QueryStr = queryStr;
    m_CreateQueryStr = createQueryStr;
    m_UpdateQueryStr = updateQueryStr;

    model = new QSqlQueryModel(this);

    ui->parameterComboBox->setModel(model);

    ui->recommendationTextEdit->setText(recommendation);

    display();
}

ParameterValueForm::~ParameterValueForm()
{
    delete ui;

    qDebug() << "ParameterValue Form is destroyed";
}

void ParameterValueForm::display()
{
    model->setQuery(m_QueryStr);

    ui->parameterComboBox->setModelColumn(1);

    dataBind();
}

void ParameterValueForm::acceptCreate(int recommendationFromId, QString fieldKey)
{
    int parameterId = -1;

    QModelIndex parameterIdIndex = model->index(ui->parameterComboBox->currentIndex(), 0);

    if(parameterIdIndex.isValid()) parameterId = parameterIdIndex.data().toInt();

    if(parameterId >= 0)
    {
        QSqlQuery query;

        query.prepare(m_CreateQueryStr);
        query.addBindValue(recommendationFromId);
        query.addBindValue(fieldKey);
        query.addBindValue(parameterId);
        query.addBindValue(ui->recommendationTextEdit->toPlainText());
        query.addBindValue(ui->recommendationTextEdit->toPlainText());
        query.addBindValue(ui->recommendationTextEdit->toPlainText());

        bool queryExecuted = query.exec();

        qDebug() << "Query executed: " << queryExecuted;

        if(!queryExecuted)
        {
            qDebug() << "Query execution error: " << query.lastError();
        }
    }
}

void ParameterValueForm::acceptEdit()
{
    int parameterId = -1;

    QModelIndex parameterIdIndex = model->index(ui->parameterComboBox->currentIndex(), 0);

    if(parameterIdIndex.isValid()) parameterId = parameterIdIndex.data().toInt();

    if(parameterId >= 0)
    {
        QSqlQuery query;

        query.prepare(m_UpdateQueryStr);
        query.addBindValue(parameterId);
        query.addBindValue(ui->recommendationTextEdit->toPlainText());
        query.addBindValue(m_Id);

        bool queryExecuted = query.exec();

        qDebug() << "Query executed: " << queryExecuted;

        if(!queryExecuted)
        {
            qDebug() << "Query execution error: " << query.lastError();
        }
    }
}

void ParameterValueForm::currentIndexChanged(int index)
{
    QModelIndex idIndex = model->index(index, 0);

    if(idIndex.isValid()) m_ParameterId = idIndex.data().toInt();
}

void ParameterValueForm::dataBind()
{
    for(int i = 0; i < model->rowCount(); i++)
    {
        int parameterId = model->index(i, 0).data().toInt();

        if(m_ParameterId == parameterId) ui->parameterComboBox->setCurrentIndex(i);
    }
}
