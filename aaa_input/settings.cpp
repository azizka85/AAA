#include <QString>
#include <QStringList>
#include <QMap>
#include <QSqlDatabase>
#include <QApplication>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
\
#include "settings.h"

Settings* Settings::settingsInstance = 0;

Settings::Settings(const QMap<QString, QString>& data)
{
    localeAliases["kazakh"] = "kz";
    localeAliases["russian"] = "ru";
    localeAliases["english"] = "en";

    m_RecommendationIndex = data.value("recommendationIndex", "0").toInt();

    m_Locale = data.value("locale", "english");

    m_DBPath = data.value("dbPath", "AAA.db");

    m_DB = QSqlDatabase::addDatabase("QSQLITE");

    m_DB.setDatabaseName(m_DBPath);    
}

void Settings::init(const QMap<QString, QString>& data)
{
    releaseSettings();

    settingsInstance = new Settings(data);
}

Settings *Settings::get()
{
    return settingsInstance;
}

void Settings::releaseSettings()
{
    if(settingsInstance != 0) delete settingsInstance;

    settingsInstance = 0;
}

QString Settings::dbPath()
{
    return m_DBPath;
}

void Settings::setDBPath(QString dbPath)
{
    closeDB();

    m_DB.setDatabaseName(dbPath);

    m_DBPath = dbPath;
}

QString Settings::locale()
{
    return m_Locale;
}

void Settings::setLocale(QString locale)
{
    m_Locale = locale;

    qDebug() << "Settings locale changed to " << locale;
}

int Settings::recommendationIndex()
{
    return m_RecommendationIndex;
}

void Settings::setRecommendationIndex(int recommendationIndex)
{
    m_RecommendationIndex = recommendationIndex;
}

QSqlDatabase Settings::db()
{
    return m_DB;
}

void Settings::loadDataFromArgs(QMap<QString, QString> &data)
{
    for (int i = 1; i < qApp->arguments().length(); i++)
    {
        QString parameter = qApp->arguments().at(i);

        QStringList keyVal = parameter.split('=');

        data[keyVal[0]] = keyVal[1];

        qDebug() << keyVal[0] << " = " << keyVal[1];
    }
}

void Settings::loadDataFromFile(QMap<QString, QString> &data)
{
    QFile file("settings.xml");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QDomDocument document;

    if(!document.setContent(&file))
    {
        file.close();
        return;
    }

    file.close();

    QDomElement settingsElement = document.documentElement();

    if(!settingsElement.isNull())
    {
        QDomNodeList childs = settingsElement.childNodes();

        int count = childs.count();

        for(int i = 0; i < count; i++)
        {
            QDomNode node = childs.at(i);

            if(!node.isNull() && node.isElement())
            {
                QDomElement element = node.toElement();

                QString name = element.tagName();
                QString value = element.text();

                data[name] = value;
            }
        }
    }
}

void Settings::save()
{
    QDomDocument document;

    QDomElement settingsElement = document.createElement("settings");


    QDomElement dbPathElement = document.createElement("dbPath");

    QDomText dbPathText = document.createTextNode(m_DBPath);

    dbPathElement.appendChild(dbPathText);


    QDomElement localeElement = document.createElement("locale");

    QDomText localeText = document.createTextNode(m_Locale);

    localeElement.appendChild(localeText);


    QDomElement recommendationIndexElement = document.createElement("recommendationIndex");

    QDomText recommendationIndexText = document.createTextNode(QString::number(m_RecommendationIndex));

    recommendationIndexElement.appendChild(recommendationIndexText);


    settingsElement.appendChild(dbPathElement);
    settingsElement.appendChild(localeElement);
    settingsElement.appendChild(recommendationIndexElement);

    document.appendChild(settingsElement);


    QDomNode xmlNode = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");

    document.insertBefore(xmlNode, document.firstChild());

    QFile file("settings.xml");

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    document.save(out, 3);

    file.close();
}

void Settings::closeDB()
{
    if(m_DB.isOpen()) m_DB.close();
}

Settings::~Settings()
{
    closeDB();

    save();

    qDebug() << "db closed";
}

QString Settings::shortLocale()
{
    return localeAliases.contains(m_Locale) ? localeAliases[m_Locale] : "en";
}
