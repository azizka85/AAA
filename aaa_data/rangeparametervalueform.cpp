#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "rangeparametervalueform.h"
#include "ui_rangeparametervalueform.h"

RangeParameterValueForm::RangeParameterValueForm(double rangeMin, double rangeMax, int decimals, int id, int parameterId, QString recommendation, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr, QVBoxLayout *parent) :
    QWidget(parent->widget()),
    ui(new Ui::RangeParameterValueForm)
{
    ui->setupUi(this);

    m_Id = id;
    m_ParameterId = parameterId;

    m_QueryStr = queryStr;
    m_CreateQueryStr = createQueryStr;
    m_CreateParameterQueryStr = createParameterQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_UpdateParameterQueryStr = updateParameterQueryStr;

    ui->recommendationTextEdit->setText(recommendation);

    ui->minLineEdit->setValidator(new QDoubleValidator(rangeMin, rangeMax, decimals, this));
    ui->maxLineEdit->setValidator(new QDoubleValidator(rangeMin, rangeMax, decimals, this));

    display();
}

RangeParameterValueForm::~RangeParameterValueForm()
{
    delete ui;

    qDebug() << "RangeParameterValue Form is destroyed";
}

void RangeParameterValueForm::display()
{
    dataBind();
}

void RangeParameterValueForm::acceptCreate(int recommendationFromId, QString fieldKey)
{
    int parameterId = -1;

    QSqlQuery parameterQuery;

    QVariant min = ui->minLineEdit->text().isEmpty() ? QString() : ui->minLineEdit->text();
    QVariant max = ui->maxLineEdit->text().isEmpty() ? QString() : ui->maxLineEdit->text();

    parameterQuery.prepare(m_CreateParameterQueryStr);
    parameterQuery.addBindValue(min);
    parameterQuery.addBindValue(max);

    bool parameterQueryExecuted = parameterQuery.exec();

    qDebug() << "Parameter Query executed: " << parameterQueryExecuted;

    if(!parameterQueryExecuted)
    {
        qDebug() << "Parameter Query execution error: " << parameterQuery.lastError();
    }

    parameterId = parameterQuery.lastInsertId().toInt();

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

void RangeParameterValueForm::acceptEdit()
{
    if(m_ParameterId >= 0)
    {
        QVariant min = ui->minLineEdit->text().isEmpty() ? QString() : ui->minLineEdit->text();
        QVariant max = ui->maxLineEdit->text().isEmpty() ? QString() : ui->maxLineEdit->text();

        QSqlQuery parameterQuery;

        parameterQuery.prepare(m_UpdateParameterQueryStr);
        parameterQuery.addBindValue(min);
        parameterQuery.addBindValue(max);
        parameterQuery.addBindValue(m_ParameterId);

        bool parameterQueryExecuted = parameterQuery.exec();

        qDebug() << "Parameter Query executed: " << parameterQueryExecuted;

        if(!parameterQueryExecuted)
        {
            qDebug() << "Parameter Query execution error: " << parameterQuery.lastError();
        }

        QSqlQuery query;

        query.prepare(m_UpdateQueryStr);
        query.addBindValue(m_ParameterId);
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

void RangeParameterValueForm::dataBind()
{
    qDebug() << "RangeParameterValueForm::dataBind - " << m_QueryStr;

    QSqlQuery query;

    query.prepare(m_QueryStr);
    query.addBindValue(m_ParameterId);

    bool queryExecuted = query.exec();

    qDebug() << "Query executed: " << queryExecuted;

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    while(query.next())
    {
        ui->minLineEdit->setText(query.value(0).toString());
        ui->maxLineEdit->setText(query.value(1).toString());
    }
}
