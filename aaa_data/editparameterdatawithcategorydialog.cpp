#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "editparameterdatawithcategorydialog.h"
#include "ui_editparameterdatawithcategorydialog.h"

EditParameterDataWithCategoryDialog::EditParameterDataWithCategoryDialog(int id, int categoryId, QString selectQueryStr, QString updateQueryStr, QString categoryQueryStr,
    QString boxEditTitle, QString categoryHeaderData, QString nameHeaderData, QString descriptionHeaderData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditParameterDataWithCategoryDialog)
{
    ui->setupUi(this);

    m_Id = id;
    m_CategoryId = categoryId;

    m_SelectQueryStr = selectQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_CategoryQueryStr = categoryQueryStr;

    ui->groupBox->setTitle(boxEditTitle.arg(id));

    ui->categoryLabel->setText(categoryHeaderData);
    ui->nameLabel->setText(nameHeaderData);
    ui->descriptionLabel->setText(descriptionHeaderData);

    categoryModel = new QSqlQueryModel(this);

    ui->categoryComboBox->setModel(categoryModel);

    displayData();
}

EditParameterDataWithCategoryDialog::~EditParameterDataWithCategoryDialog()
{
    delete ui;

    qDebug() << "EditParameterDataWithCategory Dialog is destroyed";
}

void EditParameterDataWithCategoryDialog::acceptedEditData()
{
    QModelIndex idIndex = categoryModel->index(ui->categoryComboBox->currentIndex(), 0);

    int categoryId = categoryModel->data(idIndex).toInt();

    QSqlQuery query;

    query.prepare(m_UpdateQueryStr);
    query.addBindValue(categoryId);
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

void EditParameterDataWithCategoryDialog::displayData()
{
    categoryModel->setQuery(m_CategoryQueryStr);

    ui->categoryComboBox->setModelColumn(1);

    categoryDataBind();

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

void EditParameterDataWithCategoryDialog::categoryDataBind()
{
    for(int i = 0; i < categoryModel->rowCount(); i++)
    {
        int categoryId = categoryModel->index(i, 0).data().toInt();

        if(categoryId == m_CategoryId) ui->categoryComboBox->setCurrentIndex(i);
    }
}
