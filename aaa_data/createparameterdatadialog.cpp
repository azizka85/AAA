#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "createparameterdatadialog.h"
#include "ui_createparameterdatadialog.h"

CreateParameterDataDialog::CreateParameterDataDialog(QString boxCreateTitle, QString createQueryStr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateParameterDataDialog)
{
    ui->setupUi(this);

    ui->groupBox->setTitle(boxCreateTitle);

    m_CreateQueryStr = createQueryStr;
}

CreateParameterDataDialog::~CreateParameterDataDialog()
{
    delete ui;

    qDebug() << "CreateParameterData dialog is destroyed";
}

void CreateParameterDataDialog::acceptCreateData()
{
    QSqlQuery query;

    query.prepare(m_CreateQueryStr);
    query.addBindValue(ui->nameLineEdit->text());
    query.addBindValue(ui->descriptionTextEdit->toPlainText());
    query.addBindValue(ui->nameLineEdit->text());
    query.addBindValue(ui->descriptionTextEdit->toPlainText());
    query.addBindValue(ui->nameLineEdit->text());
    query.addBindValue(ui->descriptionTextEdit->toPlainText());

    bool queryExecuted = query.exec();

    qDebug() << "Query executed: " << queryExecuted;

    if(!queryExecuted)
    {
        qDebug() << "Query execution error: " << query.lastError();
    }

    close();
}
