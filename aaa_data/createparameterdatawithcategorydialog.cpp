#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "createparameterdatawithcategorydialog.h"
#include "ui_createparameterdatawithcategorydialog.h"

CreateParameterDataWithCategoryDialog::CreateParameterDataWithCategoryDialog(QString boxCreateTitle, QString createQueryStr, QString categoryQueryStr,
        QString categoryHeaderData, QString nameHeaderData, QString descriptionHeaderData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateParameterDataWithCategoryDialog)
{
    ui->setupUi(this);

    ui->groupBox->setTitle(boxCreateTitle);

    ui->categoryLabel->setText(categoryHeaderData);
    ui->nameLabel->setText(nameHeaderData);
    ui->descriptionLabel->setText(descriptionHeaderData);

    m_CreateQueryStr = createQueryStr;
    m_CategoryQueryStr = categoryQueryStr;

    categoryModel = new QSqlQueryModel(this);

    ui->categoryComboBox->setModel(categoryModel);

    displayCategoryList();
}

CreateParameterDataWithCategoryDialog::~CreateParameterDataWithCategoryDialog()
{
    delete ui;

    qDebug() << "CreateParameterDataWithCategory Dialog is destroyed";
}

void CreateParameterDataWithCategoryDialog::acceptCreateData()
{
    QModelIndex categoryIdIndex = categoryModel->index(ui->categoryComboBox->currentIndex(), 0);

    int categoryId = categoryModel->data(categoryIdIndex).toInt();

    QSqlQuery query;

    query.prepare(m_CreateQueryStr);
    query.addBindValue(categoryId);
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

void CreateParameterDataWithCategoryDialog::displayCategoryList()
{
    categoryModel->setQuery(m_CategoryQueryStr);

    ui->categoryComboBox->setModelColumn(1);

    ui->categoryComboBox->setCurrentIndex(0);
}
