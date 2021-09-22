#include <QApplication>

#include "mainwindow.h"

#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMap<QString, QString> data;

    Settings::loadDataFromFile(data);
    Settings::loadDataFromArgs(data);

    Settings::init(data);

    MainWindow w;
    w.show();

    return a.exec();
}
