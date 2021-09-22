#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QMap>
#include <QSqlDatabase>

#include "parametervalue.h"
#include "rangeparametervalue.h"
#include "parametervaluewithtype.h"
#include "rangeparametervaluewithtype.h"
#include "comparisonparametervalue.h"

class Settings
{
private:
    static Settings* settingsInstance;

private:
    Settings(const QMap<QString, QString>& data);

public:

    static void init(const QMap<QString, QString>& data);
    static Settings* get();
    static void free();

    static void loadDataFromArgs(QMap<QString, QString>& data);
    static void loadDataFromFile(QMap<QString, QString>& data);

    void save();

    QString dbPath();
    void setDBPath(QString dbPath);

    QString locale();
    void setLocale(QString locale);

    QString shortLocale();

    int recommendationIndex();
    void setRecommendationIndex(int recommendationIndex);

    QSqlDatabase db();

    QMap<QString, ParameterValue*> formMap;

    QStringList criteriaList;

    ~Settings();

protected:
    QString m_DBPath;
    QString m_Locale;

    QMap<QString, QString> localeAliases;

    int m_RecommendationIndex;    

    QSqlDatabase m_DB;

    void initializeFormMap();

    void initializeCriteriaList();

    void closeDB();
};

#endif // SETTINGS_H
