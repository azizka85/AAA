#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "editparameterdatadialog.h"
#include "ui_editparameterdatadialog.h"

EditParameterDataDialog::EditParameterDataDialog(int id, QString selectQueryStr, QString updateQueryStr, QString boxEditTitle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditParameterDataDialog)
{
    ui->setupUi(this);

    m_Id = id;

    m_SelectQueryStr = selectQueryStr;
    m_UpdateQueryStr = updateQueryStr;

    ui->groupBox->setTitle(boxEditTitle.arg(id));

    displayData();
}

EditParameterDataDialog::~EditParameterDataDialog()
{
    delete ui;

    qDebug() << "EditParameterData dialog is destroyed";
}

void EditParameterDataDialog::acceptedEditData()
{
    QSqlQuery query;

    query.prepare(m_UpdateQueryStr);
    query.addBindValue(ui->nameLineEdit->text());
    query.addBindValue(ui->descriptionTextEdit->toPlainText());
    query.addBindValue(m_Id);

    bool queryExecuted = query.exec();

    qDebug() << "Query executed: " << queryExecuted;

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    close();
}

void EditParameterDataDialog::displayData()
{
    QSqlQuery query;

    query.prepare(m_SelectQueryStr);
    query.addBindValue(m_Id);

    bool queryExecuted = query.exec();

    qDebug() << "Query executed: " << queryExecuted;

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    while(query.next())
    {
        ui->nameLineEdit->setText(query.value(0).toString());
        ui->descriptionTextEdit->setText(query.value(1).toString());
    }
}

