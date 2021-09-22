#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "parametervaluewithtypeform.h"
#include "ui_parametervaluewithtypeform.h"

ParameterValueWithTypeForm::ParameterValueWithTypeForm(int id, int typeId, int parameterId, QString recommendation, QString queryStr, QString typeQueryStr, QString createQueryStr, QString updateQueryStr, QVBoxLayout *parent) :
    QWidget(parent->widget()),
    ui(new Ui::ParameterValueWithTypeForm)
{
    ui->setupUi(this);

    m_Id = id;
    m_TypeId = typeId;
    m_ParameterId = parameterId;

    m_QueryStr = queryStr;
    m_TypeQueryStr = typeQueryStr;
    m_CreateQueryStr = createQueryStr;
    m_UpdateQueryStr = updateQueryStr;

    model = new QSqlQueryModel(this);

    ui->parameterComboBox->setModel(model);

    typeModel = new QSqlQueryModel(this);

    ui->typeComboBox->setModel(typeModel);

    ui->recommendationTextEdit->setText(recommendation);

    display();
}

ParameterValueWithTypeForm::~ParameterValueWithTypeForm()
{
    delete ui;

    qDebug() << "ParameterValueWithType Form is destroyed";
}

void ParameterValueWithTypeForm::display()
{
    typeModel->setQuery(m_TypeQueryStr);

    ui->typeComboBox->setModelColumn(1);

    dataBindTypeId();
}

void ParameterValueWithTypeForm::acceptCreate(int recommendationFromId, QString fieldKey)
{
    if(m_ParameterId >= 0)
    {
        QSqlQuery query;

        query.prepare(m_CreateQueryStr);
        query.addBindValue(recommendationFromId);
        query.addBindValue(fieldKey);
        query.addBindValue(m_ParameterId);
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

void ParameterValueWithTypeForm::acceptEdit()
{
    if(m_ParameterId >= 0)
    {
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

void ParameterValueWithTypeForm::currentIndexChanged(int index)
{
    QModelIndex idIndex = model->index(index, 0);

    if(idIndex.isValid()) m_ParameterId = idIndex.data().toInt();
}

void ParameterValueWithTypeForm::currentTypeIndexChanged(int index)
{
    QModelIndex typeIdIndex = typeModel->index(index, 0);

    if(typeIdIndex.isValid()) m_TypeId = typeIdIndex.data().toInt();

    displayParameterList();
}

void ParameterValueWithTypeForm::displayParameterList()
{
    model->setQuery(m_QueryStr.arg(m_TypeId));

    ui->parameterComboBox->setModelColumn(1);

    dataBindParameterId();
}

void ParameterValueWithTypeForm::dataBindTypeId()
{
    for(int i = 0; i < typeModel->rowCount(); i++)
    {
        int typeId = typeModel->index(i, 0).data().toInt();

        if(m_TypeId == typeId) ui->typeComboBox->setCurrentIndex(i);
    }
}

void ParameterValueWithTypeForm::dataBindParameterId()
{
    for(int i = 0; i < model->rowCount(); i++)
    {
        int parameterId = model->index(i, 0).data().toInt();

        if(m_ParameterId == parameterId) ui->parameterComboBox->setCurrentIndex(i);
    }
}
