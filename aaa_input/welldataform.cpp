#include <QDebug>

#include "welldataform.h"
#include "ui_welldataform.h"

WellDataForm::WellDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WellDataForm)
{
    Vtbg = 0;
    Lpz = 0;

    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->wd_min_inside_diameter_lineedit->setValidator(validator);

    ui->wd_well_bore_radius_lineedit->setValidator(validator);

    ui->wd_perforated_interval_begin_lineedit->setValidator(validator);
    ui->wd_perforated_interval_end_lineedit->setValidator(validator);

    ui->wd_total_depth_lineedit->setValidator(validator);

    ui->wd_flowing_bottom_hole_pressure_lineedit->setValidator(validator);

    ui->wd_tubing_volume_lineedit->setValidator(validator);

    ui->wd_casing_volume_below_packer_lineedit->setValidator(validator);

    ui->wd_completion_od_lineedit->setValidator(validator);

    ui->wd_completion_id_lineedit->setValidator(validator);

    ui->wd_tubing_end_lineedit->setValidator(validator);


    wellTypeModel = new QSqlQueryModel(this);

    ui->wd_well_type_combobox->setModel(wellTypeModel);


    deviationModel = new QSqlQueryModel(this);

    ui->wd_deviation_combobox->setModel(deviationModel);


    completionTypeModel = new QSqlQueryModel(this);

    ui->wd_completion_type_combobox->setModel(completionTypeModel);


    holeTypeModel = new QSqlQueryModel(this);

    ui->wd_hole_type_combobox->setModel(holeTypeModel);
}

WellDataForm::~WellDataForm()
{
    delete ui;

    qDebug() << "WellDataForm is destroyed";
}

void WellDataForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    wellTypeModel->setQuery("select id, name_en from well_type");

    ui->wd_well_type_combobox->setModelColumn(1);

    ui->wd_well_type_combobox->setCurrentIndex(0);


    deviationModel->setQuery("select id, name_en from deviation");

    ui->wd_deviation_combobox->setModelColumn(1);

    ui->wd_deviation_combobox->setCurrentIndex(0);


    completionTypeModel->setQuery("select id, name_en from completion_type");

    ui->wd_completion_type_combobox->setModelColumn(1);

    ui->wd_completion_type_combobox->setCurrentIndex(0);


    holeTypeModel->setQuery("select id, name_en from hole_type");

    ui->wd_hole_type_combobox->setModelColumn(1);

    ui->wd_hole_type_combobox->setCurrentIndex(0);



    if(formData.contains("wd_paz_zone_length")) Lpz = formData["wd_paz_zone_length"].toDouble();


    if(formData.contains("wd_well_type")) wellTypeDataBind(formData["wd_well_type"].toInt());

    if(formData.contains("wd_deviation")) deviationDataBind(formData["wd_deviation"].toInt());

    if(formData.contains("wd_completion_type")) completionDataBind(formData["wd_completion_type"].toInt());

    if(formData.contains("wd_hole_type")) holeTypeDataBind(formData["wd_hole_type"].toInt());



    if(formData.contains("wd_min_inside_diameter")) ui->wd_min_inside_diameter_lineedit->setText(formData["wd_min_inside_diameter"].toString());

    if(formData.contains("wd_well_bore_radius")) ui->wd_well_bore_radius_lineedit->setText(formData["wd_well_bore_radius"].toString());

    if(formData.contains("wd_perforated_interval_begin")) ui->wd_perforated_interval_begin_lineedit->setText(formData["wd_perforated_interval_begin"].toString());

    if(formData.contains("wd_perforated_interval_end")) ui->wd_perforated_interval_end_lineedit->setText(formData["wd_perforated_interval_end"].toString());

    if(formData.contains("wd_total_depth")) ui->wd_total_depth_lineedit->setText(formData["wd_total_depth"].toString());

    if(formData.contains("wd_flowing_bottom_hole_pressure")) ui->wd_flowing_bottom_hole_pressure_lineedit->setText(formData["wd_flowing_bottom_hole_pressure"].toString());

    if(formData.contains("wd_tubing_volume")) ui->wd_tubing_volume_lineedit->setText(formData["wd_tubing_volume"].toString());

    if(formData.contains("wd_casing_volume_below_packer")) ui->wd_casing_volume_below_packer_lineedit->setText(formData["wd_casing_volume_below_packer"].toString());

    if(formData.contains("wd_completion_od")) ui->wd_completion_od_lineedit->setText(formData["wd_completion_od"].toString());

    if(formData.contains("wd_completion_id")) ui->wd_completion_id_lineedit->setText(formData["wd_completion_id"].toString());

    if(formData.contains("wd_primary_cementing")) ui->wd_primary_cementing_checkbox->setChecked(formData["wd_primary_cementing"].toBool());

    if(formData.contains("wd_tubing_end")) ui->wd_tubing_end_lineedit->setText(formData["wd_tubing_end"].toString());

    calculate();
}

void WellDataForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["wd_paz_zone_length"] = Lpz;


    int index = ui->wd_well_type_combobox->currentIndex();

    if(index >= 0) formData["wd_well_type"] = wellTypeModel->index(index, 0).data().toInt();

    index = ui->wd_deviation_combobox->currentIndex();

    if(index >= 0) formData["wd_deviation"] = deviationModel->index(index, 0).data().toInt();

    index = ui->wd_completion_type_combobox->currentIndex();

    if(index >= 0) formData["wd_completion_type"] = deviationModel->index(index, 0).data().toInt();

    index = ui->wd_hole_type_combobox->currentIndex();

    if(index >= 0) formData["wd_hole_type"] = holeTypeModel->index(index, 0).data().toInt();



    formData["wd_min_inside_diameter"] = ui->wd_min_inside_diameter_lineedit->text();

    formData["wd_well_bore_radius"] = ui->wd_well_bore_radius_lineedit->text();

    formData["wd_perforated_interval_begin"] = ui->wd_perforated_interval_begin_lineedit->text();

    formData["wd_perforated_interval_end"] = ui->wd_perforated_interval_end_lineedit->text();

    formData["wd_total_depth"] = ui->wd_total_depth_lineedit->text();

    formData["wd_flowing_bottom_hole_pressure"] = ui->wd_flowing_bottom_hole_pressure_lineedit->text();

    formData["wd_tubing_volume"] = ui->wd_tubing_volume_lineedit->text();

    formData["wd_casing_volume_below_packer"] = ui->wd_casing_volume_below_packer_lineedit->text();

    formData["wd_completion_od"] = ui->wd_completion_od_lineedit->text();

    formData["wd_completion_id"] = ui->wd_completion_id_lineedit->text();

    formData["wd_primary_cementing"] = ui->wd_primary_cementing_checkbox->isChecked();

    formData["wd_tubing_end"] = ui->wd_tubing_end_lineedit->text();
}

void WellDataForm::textEdited()
{
    qDebug() << "WellDataForm::textEdited";

    calculate();
}

void WellDataForm::wellTypeDataBind(int id)
{
    for(int i = 0; i < wellTypeModel->rowCount(); i++)
    {
        int cid = wellTypeModel->index(i, 0).data().toInt();

        if(id == cid) ui->wd_well_type_combobox->setCurrentIndex(i);
    }
}

void WellDataForm::deviationDataBind(int id)
{
    for(int i = 0; i < deviationModel->rowCount(); i++)
    {
        int cid = deviationModel->index(i, 0).data().toInt();

        if(id == cid) ui->wd_deviation_combobox->setCurrentIndex(i);
    }
}

void WellDataForm::completionDataBind(int id)
{
    for(int i = 0; i < completionTypeModel->rowCount(); i++)
    {
        int cid = completionTypeModel->index(i, 0).data().toInt();

        if(id == cid) ui->wd_completion_type_combobox->setCurrentIndex(i);;
    }
}

void WellDataForm::holeTypeDataBind(int id)
{
    for(int i = 0; i < holeTypeModel->rowCount(); i++)
    {
        int cid = holeTypeModel->index(i, 0).data().toInt();

        if(id == cid) ui->wd_hole_type_combobox->setCurrentIndex(i);
    }
}

void WellDataForm::calculate()
{
    double L = ui->wd_tubing_end_lineedit->text().toDouble();
    double minID = ui->wd_min_inside_diameter_lineedit->text().toDouble();

    double Hpb = ui->wd_perforated_interval_begin_lineedit->text().toDouble();
    double Hpe = ui->wd_perforated_interval_end_lineedit->text().toDouble();

    Vtbg = minID*minID*L/1029;
    Lpz = Hpe - Hpb;

    ui->wd_tubing_volume_lineedit->setText(QString::number(Vtbg));
}
