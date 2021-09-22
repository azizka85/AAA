#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTranslator>
#include <QString>
#include <QMap>
#include <QModelIndex>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QSqlQueryModel>

#include "formdata.h"

#include "inputparameter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setBoxTitle(QString boxTitle);

public slots:
    void treeWidgetItemClicked(QTreeWidgetItem * item, int column);
    void saveData();
    void openData();
    void recommendationFromIndexChanged(int index);
    void openChangeDatabaseDialog();
    void languageChanged(QAction* action);

private:
    Ui::MainWindow *ui;

    int currentId;

    int recommendationId;

    QTranslator *translator;

    QSqlQueryModel *recommendationFromListModel;

    QMap<QString, QVariant> formData;

    QMap<QString, QString> fieldMap;

    QMap<int, QString> categoryMap;

    QMap<int, FormData*> formMap;    

    QMap<QString, InputParameter*> parameterMap;

    QWidget* currentForm;
    FormData* currentFormData;

    void initializeFormMap();

    void initializeParameterMap();

    void initializeRecommendationId();

    void loadCategoryMap();

    void loadFieldMap();

    void displayFormList();

    void displayFormListItem(QTreeWidgetItem* item);

    void displayForm(int id);

    void displayRecommendationFromList();

    void displayStatus(bool opened);
};

#endif // MAINWINDOW_H
