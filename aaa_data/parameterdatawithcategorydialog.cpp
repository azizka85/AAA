#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "parameterdatawithcategorydialog.h"
#include "ui_parameterdatawithcategorydialog.h"

#include "createparameterdatawithcategorydialog.h"
#include "editparameterdatawithcategorydialog.h"

ParameterDataWithCategoryDialog::ParameterDataWithCategoryDialog(QString queryStr,
                                                                 QString selectQueryStr, QString createQueryStr, QString updateQueryStr, QString deleteQueryStr,
                                                                 QString categoryQueryStr,
                                                                 QString boxCreateTitle, QString boxUpdateTitle, QString boxDeleteTitle, QString boxDeleteQuestion,
                                                                 QString categoryHeaderData, QString nameHeaderData, QString descriptionHeaderData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterDataWithCategoryDialog)
{
    ui->setupUi(this);

    m_QueryStr = queryStr;

    m_SelectQueryStr = selectQueryStr;
    m_CreateQueryStr = createQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_DeleteQueryStr = deleteQueryStr;

    m_CategoryQueryStr = categoryQueryStr;

    m_BoxCreateTitle = boxCreateTitle;
    m_BoxUpdateTitle = boxUpdateTitle;
    m_BoxDeleteTitle = boxDeleteTitle;

    m_BoxDeleteQuestion = boxDeleteQuestion;

    m_CategoryHeaderData = categoryHeaderData;
    m_NameHeaderData = nameHeaderData;
    m_DescriptionHeaderData = descriptionHeaderData;

    queryModel = new QSqlQueryModel(this);

    model = new ParameterDataWithCategoryModel(this);

    model->setSourceModel(queryModel);

    ui->tableView->setModel(model);

    tableViewContextMenu = new QMenu(this);

    tableViewContextMenu->addAction(ui->actionCreate);
    tableViewContextMenu->addAction(ui->actionEdit);
    tableViewContextMenu->addAction(ui->actionDelete);

    connect(tableViewContextMenu, SIGNAL(triggered(QAction*)), this, SLOT(contextMenuTriggered(QAction*)));

    displayData();
}

ParameterDataWithCategoryDialog::~ParameterDataWithCategoryDialog()
{
    delete ui;

    qDebug() << "ParameterDataWithCategory Dialog is destroyed";
}

void ParameterDataWithCategoryDialog::contextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->tableView->indexAt(pos);

    int row = index.row();
    int column = index.column();

    ui->actionCreate->setEnabled(!m_CreateQueryStr.isEmpty());
    ui->actionEdit->setEnabled(index.isValid() && (column == 3 || column == 4) && !m_UpdateQueryStr.isEmpty());
    ui->actionDelete->setEnabled(index.isValid() && (column == 3 || column == 4) && !m_DeleteQueryStr.isEmpty());

    currentIndex = index;

    tableViewContextMenu->popup(ui->tableView->viewport()->mapToGlobal(pos));

    qDebug() << QString("Table view context menu: row=%0, column=%1").arg(row).arg(column);
}

void ParameterDataWithCategoryDialog::contextMenuTriggered(QAction *action)
{
    qDebug() << QString("Table view context menu action triggered: action=%0, row=%1, column=%2").arg(action->objectName()).arg(currentIndex.row()).arg(currentIndex.column());

    int dataId = -1;
    int categoryId = -1;

    if(currentIndex.isValid())
    {
        QModelIndex idIndex = queryModel->index(currentIndex.row(), 0);

        dataId = queryModel->data(idIndex).toInt();

        QModelIndex categoryIdIndex = queryModel->index(currentIndex.row(), 1);

        categoryId = queryModel->data(categoryIdIndex).toInt();
    }

    if(action->objectName() == QString("actionCreate"))
    {
        CreateParameterDataWithCategoryDialog* dialog = new CreateParameterDataWithCategoryDialog(m_BoxCreateTitle, m_CreateQueryStr, m_CategoryQueryStr,
                                                                m_CategoryHeaderData, m_NameHeaderData, m_DescriptionHeaderData, this);

        dialog->setAttribute(Qt::WA_DeleteOnClose);

        dialog->exec();

        displayData();
    }
    else if(action->objectName() == QString("actionEdit"))
    {
        EditParameterDataWithCategoryDialog* dialog = new EditParameterDataWithCategoryDialog(dataId, categoryId, m_SelectQueryStr, m_UpdateQueryStr, m_CategoryQueryStr,
                                                                                    m_BoxUpdateTitle, m_CategoryHeaderData, m_NameHeaderData, m_DescriptionHeaderData, this);

        dialog->setAttribute(Qt::WA_DeleteOnClose);

        dialog->exec();

        displayData();
    }
    else if(action->objectName() == QString("actionDelete"))
    {
        QString question = m_BoxDeleteQuestion.arg(dataId);

        int answer = QMessageBox::question(this, m_BoxDeleteTitle, question, QMessageBox::Yes | QMessageBox::No);

        if(answer == QMessageBox::Yes)
        {
            QSqlQuery query;

            query.prepare(m_DeleteQueryStr);
            query.addBindValue(dataId);

            bool queryExecuted = query.exec();

            qDebug() << "Query executed: " << queryExecuted;

            if(!queryExecuted)
            {
                qDebug() << "Query execution error: " << query.lastError();
            }

            displayData();
        }
    }
}

void ParameterDataWithCategoryDialog::displayData()
{
    queryModel->setQuery(m_QueryStr);

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(2, Qt::Horizontal, m_CategoryHeaderData);
    model->setHeaderData(3, Qt::Horizontal, m_NameHeaderData);
    model->setHeaderData(4, Qt::Horizontal, m_DescriptionHeaderData);

    tableViewDataBind(1, 2);

    ui->tableView->setColumnHidden(1, true);

    ui->tableView->setColumnWidth(0, 30);
    ui->tableView->setColumnWidth(2, 150);
    ui->tableView->setColumnWidth(3, 150);
    ui->tableView->setColumnWidth(4, 270);

    ui->tableView->resizeRowsToContents();
}

void ParameterDataWithCategoryDialog::tableViewDataBind(int categoryIdColumn, int categoryColumn)
{
    ui->tableView->clearSpans();

    model->categoryColumn = categoryColumn;

    int currentCategoryId = -1;
    int categoryStartIndex = -1;
    int categoryIndex = 0;
    int categoryCount = 0;

    QMap<int, QColor> categoryMap;

    for(int i = 0; i < queryModel->rowCount(); i++)
    {
        QModelIndex categoryIdIndex = queryModel->index(i, categoryIdColumn);

        int categoryId = queryModel->data(categoryIdIndex).toInt();

        if(categoryId != currentCategoryId)
        {
            if(currentCategoryId >= 0 && categoryCount > 1)
            {
                ui->tableView->setSpan(categoryStartIndex, categoryColumn, categoryCount, 1);
            }

            currentCategoryId = categoryId;

            categoryStartIndex = i;

            categoryCount = 1;

            categoryIndex++;
        }
        else
        {
            categoryCount++;
        }

        categoryMap[i] = categoryIndex % 2 == 0 ? QColor("white") : QColor(200, 255, 194);
    }

    if(currentCategoryId >= 0 && categoryCount > 1)
    {
        ui->tableView->setSpan(categoryStartIndex, categoryColumn, categoryCount, 1);
    }

    model->categoryMap = categoryMap;
}
