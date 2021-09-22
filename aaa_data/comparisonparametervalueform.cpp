#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "settings.h"

#include "comparisonparametervalueform.h"
#include "ui_comparisonparametervalueform.h"

ComparisonParameterValueForm::ComparisonParameterValueForm(int id, int fieldId, int criteriaId, int parameterId, QString recommendation, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr, QVBoxLayout *parent) :
    QWidget(parent->widget()),
    ui(new Ui::ComparisonParameterValueForm)
{
    ui->setupUi(this);

    m_Id = id;
    m_FieldId = fieldId;
    m_CriteriaId = criteriaId;
    m_ParameterId = parameterId;

    m_QueryStr = queryStr;
    m_CreateQueryStr = createQueryStr;
    m_CreateParameterQueryStr = createParameterQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_UpdateParameterQueryStr = updateParameterQueryStr;

    model = new QSqlQueryModel(this);

    criteriaModel = new QStringListModel(Settings::get()->criteriaList, this);

    ui->fieldComboBox->setModel(model);

    ui->criteriaComboBox->setModel(criteriaModel);

    ui->recommendationTextEdit->setText(recommendation);

    displayFieldList();

    criteriaDataBind();
}

ComparisonParameterValueForm::~ComparisonParameterValueForm()
{
    delete ui;

    qDebug() << "ComparisonParameterValueForm is destroyed";
}

void ComparisonParameterValueForm::acceptCreate(int recommendationFromId, QString fieldKey)
{
    int parameterId = -1;

    QModelIndex compareFieldKeyIndex = model->index(ui->fieldComboBox->currentIndex(), 2);

    if(compareFieldKeyIndex.isValid())
    {
        QString compareFieldKey = compareFieldKeyIndex.data().toString();

        QSqlQuery parameterQuery;

        parameterQuery.prepare(m_CreateParameterQueryStr);
        parameterQuery.addBindValue(compareFieldKey);
        parameterQuery.addBindValue(ui->criteriaComboBox->currentIndex());

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
}

void ComparisonParameterValueForm::acceptEdit()
{
    QModelIndex compareFieldKeyIndex = model->index(ui->fieldComboBox->currentIndex(), 2);

    if(m_ParameterId >= 0 && compareFieldKeyIndex.isValid())
    {
        QString compareFieldKey = compareFieldKeyIndex.data().toString();

        QSqlQuery parameterQuery;

        parameterQuery.prepare(m_UpdateParameterQueryStr);
        parameterQuery.addBindValue(compareFieldKey);
        parameterQuery.addBindValue(ui->criteriaComboBox->currentIndex());
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

void ComparisonParameterValueForm::displayFieldList()
{
    model->setQuery(m_QueryStr);

    ui->fieldComboBox->setModelColumn(1);

    fieldDataBind();
}

void ComparisonParameterValueForm::criteriaDataBind()
{
    if(m_CriteriaId >= 0) ui->criteriaComboBox->setCurrentIndex(m_CriteriaId);
    else ui->criteriaComboBox->setCurrentIndex(0);
}

void ComparisonParameterValueForm::fieldDataBind()
{
    ui->fieldComboBox->setCurrentIndex(0);

    for(int i = 0; i < model->rowCount(); i++)
    {
        int fieldId = model->index(i, 0).data().toInt();

        if(m_FieldId == fieldId) ui->fieldComboBox->setCurrentIndex(i);
    }
}
