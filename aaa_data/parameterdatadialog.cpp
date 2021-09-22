#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

#include "parameterdatadialog.h"
#include "ui_parameterdatadialog.h"

#include "createparameterdatadialog.h"
#include "editparameterdatadialog.h"

ParameterDataDialog::ParameterDataDialog(QString queryStr, QString selectQueryStr, QString createQueryStr, QString updateQueryStr, QString deleteQueryStr,
                                         QString boxCreateTitle, QString boxUpdateTitle, QString boxDeleteTitle, QString boxDeleteQuestion, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterDataDialog)
{
    ui->setupUi(this);

    m_QueryStr = queryStr;
    m_SelectQueryStr = selectQueryStr;
    m_CreateQueryStr = createQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_DeleteQueryStr = deleteQueryStr;

    m_BoxCreateTitle = boxCreateTitle;
    m_BoxUpdateTitle = boxUpdateTitle;
    m_BoxDeleteTitle = boxDeleteTitle;

    m_BoxDeleteQuestion = boxDeleteQuestion;

    model = new QSqlQueryModel(this);

    ui->tableView->setModel(model);

    tableViewContextMenu = new QMenu(this);

    tableViewContextMenu->addAction(ui->actionCreate);
    tableViewContextMenu->addAction(ui->actionEdit);
    tableViewContextMenu->addAction(ui->actionDelete);

    connect(tableViewContextMenu, SIGNAL(triggered(QAction*)), this, SLOT(contextMenuTriggered(QAction*)));

    displayData();
}

ParameterDataDialog::~ParameterDataDialog()
{
    delete ui;

    qDebug() << "ParameterData Dialog is destroyed";
}

void ParameterDataDialog::contextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->tableView->indexAt(pos);

    ui->actionCreate->setEnabled(!m_CreateQueryStr.isEmpty());
    ui->actionEdit->setEnabled(index.isValid() && !m_UpdateQueryStr.isEmpty());
    ui->actionDelete->setEnabled(index.isValid() && !m_DeleteQueryStr.isEmpty());

    currentIndex = index;

    tableViewContextMenu->popup(ui->tableView->viewport()->mapToGlobal(pos));

    qDebug() << QString("Table view context menu: row=%0, column=%1").arg(index.row()).arg(index.column());
}

void ParameterDataDialog::contextMenuTriggered(QAction *action)
{
    qDebug() << QString("Table view context menu action triggered: action=%0, row=%1, column=%2").arg(action->objectName()).arg(currentIndex.row()).arg(currentIndex.column());

    int dataId = -1;

    if(currentIndex.isValid())
    {
        QModelIndex idIndex = model->index(currentIndex.row(), 0);

        dataId = model->data(idIndex).toInt();
    }

    if(action->objectName() == QString("actionCreate"))
    {
        CreateParameterDataDialog* dialog = new CreateParameterDataDialog(m_BoxCreateTitle, m_CreateQueryStr, this);

        dialog->setAttribute(Qt::WA_DeleteOnClose);

        dialog->exec();

        displayData();
    }
    else if(action->objectName() == QString("actionEdit"))
    {
        EditParameterDataDialog* dialog = new EditParameterDataDialog(dataId, m_SelectQueryStr, m_UpdateQueryStr, m_BoxUpdateTitle, this);

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

void ParameterDataDialog::displayData()
{
    model->setQuery(m_QueryStr);

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Description"));

    ui->tableView->setColumnWidth(0, 30);
    ui->tableView->setColumnWidth(1, 150);
    ui->tableView->setColumnWidth(2, 200);

    ui->tableView->resizeRowsToContents();
}
