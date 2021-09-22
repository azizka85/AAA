#include <QString>
#include <QFileDialog>
#include <QSqlError>
#include <QFileInfo>
#include <QDebug>

#include "changedatabasedialog.h"
#include "ui_changedatabasedialog.h"

#include "settings.h"

ChangeDatabaseDialog::ChangeDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDatabaseDialog)
{
    ui->setupUi(this);

    displayStatus(Settings::get()->dbPath());
}

ChangeDatabaseDialog::~ChangeDatabaseDialog()
{
    qDebug() << "Change Database Dialog is destroyed";

    delete ui;
}

void ChangeDatabaseDialog::databasePathButtonClicked()
{
    QString prevPath = Settings::get()->dbPath();

    if(!prevPath.isEmpty())
    {
        QFileInfo info(prevPath);

        prevPath = info.absolutePath();
    }
    else
    {
        prevPath = "";
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"), prevPath, "Database file (*.db);; All Files (*.*)");

    displayStatus(fileName);
}

void ChangeDatabaseDialog::displayStatus(QString fileName)
{
    ui->databasePathText->setText(fileName);

    Settings::get()->setDBPath(fileName);

    qDebug() << "Path: " << Settings::get()->dbPath();

    bool opened = Settings::get()->db().open();

    if(opened)
    {
        ui->messageText->setStyleSheet(QStringLiteral("color: rgb(0, 155, 0);"));

        ui->messageText->setText(tr("Connection established"));
    }
    else
    {
        ui->messageText->setStyleSheet(QStringLiteral("color: rgb(155, 0, 0);"));

        ui->messageText->setText(Settings::get()->db().lastError().text());
    }
}
