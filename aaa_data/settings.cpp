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

    qDebug() << "recommendationIndex: " << m_RecommendationIndex;
    qDebug() << "locale: " << m_Locale;
    qDebug() << "dbPath: " << m_DBPath;

    m_DB = QSqlDatabase::addDatabase("QSQLITE");

    m_DB.setDatabaseName(m_DBPath);

    initializeFormMap();

    initializeCriteriaList();
}

void Settings::init(const QMap<QString, QString>& data)
{
    free();

    settingsInstance = new Settings(data);
}

Settings *Settings::get()
{
    return settingsInstance;
}

void Settings::free()
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

    qDeleteAll(formMap);

    formMap.clear();

    qDebug() << "db closed";
}

void Settings::initializeFormMap()
{
    double rangeMin = 0;
    double rangeMax = 0;
    int decimals = 0;

    QString compareFieldQueryStr = "";
    QString queryStr = QString("select id, name_en from well_type").arg(shortLocale());
    QString typeIdQueryStr = "";
    QString typeQueryStr = "";
    QString createQueryStr = "insert into recommendation_guide (recommendation_id, field_key, parameter_id, recommendation_kz, recommendation_ru, recommendation_en) values (?, ?, ?, ?, ?, ?)";
    QString createParameterQueryStr = "";
    QString updateQueryStr = QString("update recommendation_guide set parameter_id=?, recommendation_%1=? where id=?").arg(shortLocale());
    QString updateParameterQueryStr = "";

    formMap["wd_well_type"] = new ParameterValue(queryStr, createQueryStr, updateQueryStr);

    queryStr = QString("select id, name_%1 from completion_type").arg(shortLocale());

    formMap["wd_completion_type"] = new ParameterValue(queryStr, createQueryStr, updateQueryStr);

    rangeMin = 0;
    rangeMax = 10000;

    decimals = 0;

    queryStr = "select min, max from paz_zone_length where id=?";

    createParameterQueryStr = "insert into paz_zone_length (min, max) values (?, ?)";
    updateParameterQueryStr = "update paz_zone_length set min=?, max=? where id=?";

    formMap["wd_paz_zone_length"] = new RangeParameterValue(rangeMin, rangeMax, decimals, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    compareFieldQueryStr = "select rf.id, mid.criteria from minimum_inside_diameter mid, recommendation_field rf where rf.key=mid.field_key and mid.id=?";

    queryStr = QString("select id, name_%1, key from recommendation_field where is_recommendation_field=0").arg(shortLocale());

    createParameterQueryStr = "insert into minimum_inside_diameter (field_key, criteria) values (?, ?)";
    updateParameterQueryStr = "update minimum_inside_diameter set field_key=?, criteria=? where id=?";

    formMap["wd_min_inside_diameter"] = new ComparisonParameterValue(compareFieldQueryStr, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    compareFieldQueryStr = "select rf.id, td.criteria from total_depth td, recommendation_field rf where rf.key=td.field_key and td.id=?";

    queryStr = QString("select id, name_%1, key from recommendation_field where is_recommendation_field=0").arg(shortLocale());

    createParameterQueryStr = "insert into total_depth (field_key, criteria) values (?, ?)";
    updateParameterQueryStr = "update total_depth set field_key=?, criteria=? where id=?";

    formMap["wd_total_depth"] = new ComparisonParameterValue(compareFieldQueryStr, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    rangeMin = -1000;
    rangeMax = 1000;

    decimals = 0;

    queryStr = "select min, max from reservoir_temperature where id=?";

    createParameterQueryStr = "insert into reservoir_temperature (min, max) values (?, ?)";
    updateParameterQueryStr = "update reservoir_temperature set min=?, max=? where id=?";

    formMap["rd_reservoir_temperature"] = new RangeParameterValue(rangeMin, rangeMax, decimals, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    queryStr = QString("select id, name_%1 from reservoir_permeability").arg(shortLocale());

    formMap["rd_permeability_type"] = new ParameterValue(queryStr, createQueryStr, updateQueryStr);

    compareFieldQueryStr = "select rf.id, rp.criteria from reservoir_pressure rp, recommendation_field rf where rf.key=rp.field_key and rp.id=?";

    queryStr = QString("select id, name_%1, key from recommendation_field where is_recommendation_field=0").arg(shortLocale());

    createParameterQueryStr = "insert into reservoir_pressure (field_key, criteria) values (?, ?)";
    updateParameterQueryStr = "update reservoir_pressure set field_key=?, criteria=? where id=?";

    formMap["rd_reservoir_pressure"] = new ComparisonParameterValue(compareFieldQueryStr, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    queryStr = QString("select id, name_%1 from drive_mechanism").arg(shortLocale());

    formMap["rd_drive_mechanism"] = new ParameterValue(queryStr, createQueryStr, updateQueryStr);

    compareFieldQueryStr = "select rf.id, pp.criteria from pumping_pressure pp, recommendation_field rf where rf.key=pp.field_key and pp.id=?";

    queryStr = QString("select id, name_%1, key from recommendation_field where is_recommendation_field=0").arg(shortLocale());

    createParameterQueryStr = "insert into pumping_pressure (field_key, criteria) values (?, ?)";
    updateParameterQueryStr = "update pumping_pressure set field_key=?, criteria=? where id=?";

    formMap["rd_pumping_pressure"] = new ComparisonParameterValue(compareFieldQueryStr, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    rangeMin = 0;
    rangeMax = 100;

    decimals = 0;

    queryStr = "select min, max from water_cut where id=?";

    createParameterQueryStr = "insert into water_cut (min, max) values (?, ?)";
    updateParameterQueryStr = "update water_cut set min=?, max=? where id=?";

    formMap["pd_water_cut"] = new RangeParameterValue(rangeMin, rangeMax, decimals, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    queryStr = QString("select id, name_%1 from formation_damage where type_id=%1").arg(shortLocale());

    typeIdQueryStr = "select type_id from formation_damage where id=?";

    typeQueryStr = QString("select id, name_%1 from formation_damage_type").arg(shortLocale());

    formMap["pd_formation_damage"] = new ParameterValueWithType(queryStr, typeIdQueryStr, typeQueryStr, createQueryStr, updateQueryStr);

    rangeMin = 0;
    rangeMax = 100;

    decimals = 0;

    queryStr = "select min, max from damage_radius where id=?";

    createParameterQueryStr = "insert into damage_radius (min, max) values (?, ?)";
    updateParameterQueryStr = "update damage_radius set min=?, max=? where id=?";

    formMap["pd_damage_radius"] = new RangeParameterValue(rangeMin, rangeMax, decimals, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    rangeMin = 0;
    rangeMax = 100000;

    decimals = 0;

    queryStr = "select min, max from h2s where id=?";

    createParameterQueryStr = "insert into h2s (min, max) values (?, ?)";
    updateParameterQueryStr = "update h2s set min=?, max=? where id=?";

    formMap["pd_h2s"] = new RangeParameterValue(rangeMin, rangeMax, decimals, queryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);

    queryStr = QString("select id, name_%1 from compatibility_data").arg(shortLocale());

    formMap["ld_compatibility_data"] = new ParameterValue(queryStr, createQueryStr, updateQueryStr);

    queryStr = QString("select id, name_%1 from formation_types").arg(shortLocale());

    formMap["md_formation_types"] = new ParameterValue(queryStr, createQueryStr, updateQueryStr);

    queryStr = QString("select id, name_%1 from clays_types").arg(shortLocale());

    formMap["md_clays_types"] = new ParameterValue(queryStr, createQueryStr, updateQueryStr);

    rangeMin = 0;
    rangeMax = 100;

    decimals = 1;

    queryStr = "select min, max from acid_additives where id=?";

    typeIdQueryStr = "select acid_type_id from acid_additives where id=?";
    typeQueryStr = QString("select id, name_%1 from acid_type").arg(shortLocale());
    createParameterQueryStr = "insert into acid_additives (acid_type_id, min, max) values (?, ?, ?)";
    updateParameterQueryStr = "update acid_additives set acid_type_id=?, min=?, max=? where id=?";

    formMap["aa_additives_range"] = new RangeParameterValueWithType(rangeMin, rangeMax, decimals, queryStr, typeIdQueryStr, typeQueryStr, createQueryStr, createParameterQueryStr, updateQueryStr, updateParameterQueryStr);
}

void Settings::initializeCriteriaList()
{
    criteriaList << QObject::tr("Is empty");
    criteriaList << QObject::tr("Is not empty");
    criteriaList << QObject::tr("Equal");
    criteriaList << QObject::tr("Not equal");
    criteriaList << QObject::tr("Larger than");
    criteriaList << QObject::tr("Equal or larger than");
    criteriaList << QObject::tr("Less than");
    criteriaList << QObject::tr("Equal or less than");
}

QString Settings::shortLocale()
{
    return localeAliases.contains(m_Locale) ? localeAliases[m_Locale] : "en";
}
