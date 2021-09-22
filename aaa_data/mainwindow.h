#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTranslator>
#include <QMainWindow>
#include <QSqlQueryModel>

#include "recommendationmodel.h"
#include "parametervalue.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openAboutDialog();
    void openChangeDatabaseDialog();
    void openEditRecommendationsDialog();
    void openWellTypeDataDialog();
    void openCompletionTypeDataDialog();
    void openDeviationDialog();
    void openHoleTypeDialog();
    void openReservoirTypeDataDialog();
    void openDriveMechanismDataDialog();
    void openCompatibilityDataDialog();
    void openFormationTypeDataDialog();
    void openClaysTypesDataDialog();
    void openFormationDamageTypeDataDialog();
    void openFormationDamageDataDialog();
    void openAcidAdditivesType();
    void openRecommendationFieldCategory();
    void openRecommendationField();
    void languageChanged(QAction *action);
    void recommendationComboBoxIndexChanged(int index);
    void contextMenuRequested(const QPoint& pos);
    void contextMenuTriggered(QAction* action);

private:

    Ui::MainWindow *ui;

    QSqlQueryModel *recommendationFromListModel;
    QSqlQueryModel *recommendationQueryModel;
    RecommendationModel *recommendationModel;

    QMenu *tableViewContextMenu;

    QModelIndex currentIndex;

    QTranslator *translator;

    void displayStatus(bool opened);
    void displayRecommendationFromList();
    void displayRecommendations(int id);
    void recommendationTableViewDataBind(int fieldIdColumn, int fieldColumn, int categoryIdColumn, int categoryColumn, int parameterIdColumn, int fieldKeyColumn);
};

#endif // MAINWINDOW_H
