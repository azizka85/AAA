#include <QObject>
#include <QColor>
#include <QDebug>

#include "recommendationmodel.h"

#include "rangeparameterdata.h"
#include "parameterdatawithtype.h"
#include "rangeparameterdatawithtypes.h"
#include "comparisonparameterdata.h"

RecommendationModel::RecommendationModel(QObject *parent) : QIdentityProxyModel(parent)
{
    parameterDataMap["wd_well_type"] = new ParameterData("select name_%1 as name from well_type where id=%2");

    parameterDataMap["wd_completion_type"] = new ParameterData("select name_%1 as name from completion_type where id=%2");

    parameterDataMap["wd_paz_zone_length"] = new RangeParameterData("Lpz", "select min, max from paz_zone_length where id=%2");

    parameterDataMap["wd_min_inside_diameter"] = new ComparisonParameterData("select rf.name_%1, mid.criteria from minimum_inside_diameter mid, recommendation_field rf where rf.key=mid.field_key and mid.id=%2");

    parameterDataMap["wd_total_depth"] = new ComparisonParameterData("select rf.name_%1, td.criteria from total_depth td, recommendation_field rf where rf.key=td.field_key and td.id=%2");

    parameterDataMap["rd_reservoir_temperature"] = new RangeParameterData("Tres", "select min, max from reservoir_temperature where id=%2");

    parameterDataMap["rd_permeability_type"] = new ParameterData("select name_%1 as name from reservoir_permeability where id=%2");

    parameterDataMap["rd_reservoir_pressure"] = new ComparisonParameterData("select rf.name_%1, rp.criteria from reservoir_pressure rp, recommendation_field rf where rf.key=rp.field_key and rp.id=%2");

    parameterDataMap["rd_drive_mechanism"] = new ParameterData("select name_%1 as name from drive_mechanism where id=%2");

    parameterDataMap["rd_pumping_pressure"] = new ComparisonParameterData("select rf.name_%1, pp.criteria from pumping_pressure pp, recommendation_field rf where rf.key=pp.field_key and pp.id=%2");

    parameterDataMap["pd_water_cut"] = new RangeParameterData("WC", "select min, max from water_cut where id=%2");

    parameterDataMap["pd_formation_damage"] = new ParameterDataWithType("select fdt.name_%1 as type, fd.name_%1 as content from formation_damage fd, formation_damage_type fdt where fdt.id = fd.type_id and fd.id=%2");

    parameterDataMap["pd_damage_radius"] = new RangeParameterData("Rd", "select min, max from damage_radius where id=%2");

    parameterDataMap["pd_h2s"] = new RangeParameterData("H2S", "select min, max from h2s where id=%2");

    parameterDataMap["ld_compatibility_data"] = new ParameterData("select name_%1 as name from compatibility_data where id=%2");

    parameterDataMap["md_formation_types"] = new ParameterData("select name_%1 as name from formation_types where id=%2");

    parameterDataMap["md_clays_types"] = new ParameterData("select name_%1 as name from clays_types where id=%2");

    parameterDataMap["aa_additives_range"] = new RangeParameterDataWithTypes("select aat.name_%1, aa.min, aa.max from acid_additives aa, acid_type aat where aat.id = aa.acid_type_id and aa.id=%2");
}

RecommendationModel::~RecommendationModel()
{
    qDebug() << "RecommendationModel destroyed";

    qDeleteAll(parameterDataMap);

    parameterDataMap.clear();
}

QVariant RecommendationModel::data(const QModelIndex &index, int role) const
{
    int rowIndex = index.row();
    int column = index.column();

    if(role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else if(role == Qt::BackgroundColorRole)
    {
        if(column == fieldColumn) return fieldMap[rowIndex];
        else if(column == categoryColumn) return categoryMap[rowIndex];
        else return rowIndex % 2 == 0 ? QColor(220, 220, 220) : QColor("white");
    }
    else if(role == Qt::DisplayRole)
    {
        if(column == parameterIdColumn)
        {
            QModelIndex fieldKeyIndex = QIdentityProxyModel::index(rowIndex, fieldKeyColumn);

            QString fieldKey = QIdentityProxyModel::data(fieldKeyIndex).toString();

            int parameterId = QIdentityProxyModel::data(index).toInt();

            if(parameterDataMap.contains(fieldKey))
            {
                ParameterData* data = parameterDataMap[fieldKey];

                return data->text(parameterId);
            }
            else
            {
                return QObject::tr("Wrong field key, please contact with developer");
            }
        }
    }

    return QIdentityProxyModel::data(index, role);
}
