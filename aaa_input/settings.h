#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QMap>
#include <QSqlDatabase>

class Settings
{
private:
    static Settings* settingsInstance;

private:
    Settings(const QMap<QString, QString>& data);

public:

    static void init(const QMap<QString, QString>& data);
    static Settings* get();
    static void releaseSettings();

    static void loadDataFromArgs(QMap<QString, QString>& data);
    static void loadDataFromFile(QMap<QString, QString>& data);

    void save();

    QString shortLocale();

    QString dbPath();
    void setDBPath(QString dbPath);

    QString locale();
    void setLocale(QString locale);

    int recommendationIndex();
    void setRecommendationIndex(int recommendationIndex);

    QSqlDatabase db();

    ~Settings();

protected:
    QString m_DBPath;
    QString m_Locale;

    QMap<QString, QString> localeAliases;

    int m_RecommendationIndex;    

    QSqlDatabase m_DB;

    void closeDB();
};

#endif // SETTINGS_H
