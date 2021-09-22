#include <QtMath>
#include <QDebug>

#include "calculationdataform.h"
#include "ui_calculationdataform.h"

CalculationDataForm::CalculationDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculationDataForm)
{
    L = 0;
    minID = 0;
    q = 0;
    mu = 0;
    H = 0;
    Pfrac = 0;
    Pres = 0;
    K = 0;
    B = 0;
    Re = 0;
    Rw = 0;
    Rd = 0;
    Vtbg = 0;
    S = 0;

    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->cd_f_lineedit->setValidator(validator);

    ui->cd_kd_lineedit->setValidator(validator);

    ui->cd_t_s_lineedit->setValidator(validator);

    ui->cd_vol_acid_lineedit->setValidator(validator);

    ui->cd_vol_pump_lineedit->setValidator(validator);

    ui->cd_ro_lineedit->setValidator(validator);

    ui->cd_p_safe_lineedit->setValidator(validator);

    ui->cd_p_fric_lineedit->setValidator(validator);

    ui->cd_hydrostatic_pressure_lineedit->setValidator(validator);

    ui->cd_t_ci_lineedit->setValidator(validator);
}

CalculationDataForm::~CalculationDataForm()
{
    delete ui;

    qDebug() << "CalculationDataForm is destroyed";
}

void CalculationDataForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    dataBind(formData);

    calculate();
}

void CalculationDataForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["cd_f"] = ui->cd_f_lineedit->text();

    formData["cd_kd"] = ui->cd_kd_lineedit->text();

    formData["cd_t_s"] = ui->cd_t_s_lineedit->text();

    formData["cd_vol_acid"] = ui->cd_vol_acid_lineedit->text();

    formData["cd_vol_pump"] = ui->cd_vol_pump_lineedit->text();

    formData["cd_vol_pickling"] = ui->cd_vol_pickling_lineedit->text();

    formData["cd_ro"] = ui->cd_ro_lineedit->text();

    formData["cd_ro_d"] = ui->cd_ro_d_lineedit->text();

    formData["cd_p_safe"] = ui->cd_p_safe_lineedit->text();

    formData["cd_p_fric"] = ui->cd_p_fric_lineedit->text();

    formData["cd_hydrostatic_pressure"] = ui->cd_hydrostatic_pressure_lineedit->text();

    formData["cd_well_head_pressure"] = ui->cd_well_head_pressure_lineedit->text();

    formData["cd_q_max"] = ui->cd_q_max_lineedit->text();

    formData["cd_q_min"] = ui->cd_q_min_lineedit->text();

    formData["cd_t_ci"] = ui->cd_t_ci_lineedit->text();


    formData["wd_tubing_volume"] = Vtbg;

    formData["rd_skin_factor"] = S;
}

void CalculationDataForm::textEdited()
{
    calculate();
}

void CalculationDataForm::calculate()
{
    qDebug() << "CalculationDataForm::calculate()";

    double F = ui->cd_f_lineedit->text().toDouble();
    double Kd = ui->cd_kd_lineedit->text().toDouble();
    double ts = ui->cd_t_s_lineedit->text().toDouble();
    double ro = ui->cd_ro_lineedit->text().toDouble();
    double Psafe = ui->cd_p_safe_lineedit->text().toDouble();
    double Vacid = ui->cd_vol_acid_lineedit->text().toDouble();
    double Vpump = ui->cd_vol_pump_lineedit->text().toDouble();
    double tCI = ui->cd_t_ci_lineedit->text().toDouble();

    Vtbg = minID*minID*L/1029;
    S = (K/Kd - 1)*qLn(Rd/Rw);

    double Vpickling = 4.68743*ts*L*F*(minID + ts);
    double roD = 119.83*ro;
    double Pfric = 518*qPow(ro, 0.79)*qPow(q, 1.79)*qPow(mu, 0.207)/qPow(minID, 4.79);
    double Phyd = 0.052*roD*H;
    double Ps = Pfrac + Pfric - Phyd - Psafe;
    double Qmax = 4.916e-6*K*H*(Pfrac - Pres - Psafe)/(mu*B*qLn(Re/Rw) + S);
    double Qmin = (Vacid - Vpump)/42/60/tCI;

    ui->cd_vol_pickling_lineedit->setText(QString::number(Vpickling));
    ui->cd_ro_d_lineedit->setText(QString::number(roD));
    ui->cd_p_fric_lineedit->setText(QString::number(Pfric));
    ui->cd_hydrostatic_pressure_lineedit->setText(QString::number(Phyd));
    ui->cd_well_head_pressure_lineedit->setText(QString::number(Ps));
    ui->cd_q_max_lineedit->setText(QString::number(Qmax));
    ui->cd_q_min_lineedit->setText(QString::number(Qmin));        
}

void CalculationDataForm::dataBind(QMap<QString, QVariant> &formData)
{
    if(formData.contains("rd_reservoir_permeability")) K = formData["rd_reservoir_permeability"].toDouble();

    if(formData.contains("pd_bo")) B = formData["pd_bo"].toDouble();

    if(formData.contains("rd_fracture_pressure")) Pfrac = formData["rd_fracture_pressure"].toDouble();

    if(formData.contains("rd_reservoir_pressure")) Pres = formData["rd_reservoir_pressure"].toDouble();

    if(formData.contains("wd_tubing_end")) L = formData["wd_tubing_end"].toDouble();

    if(formData.contains("wd_min_inside_diameter")) minID = formData["wd_min_inside_diameter"].toDouble();

    if(formData.contains("pd_pumping_rate")) q = formData["pd_pumping_rate"].toDouble();

    if(formData.contains("pd_viscosity")) mu = formData["pd_viscosity"].toDouble();

    if(formData.contains("wd_total_depth")) H = formData["wd_total_depth"].toDouble();

    if(formData.contains("rd_drainage_radius")) Re = formData["rd_drainage_radius"].toDouble();

    if(formData.contains("wd_well_bore_radius")) Rw = formData["wd_well_bore_radius"].toDouble();

    if(formData.contains("pd_damage_radius")) Rd = formData["pd_damage_radius"].toDouble();

    if(formData.contains("wd_tubing_volume")) Vtbg = formData["wd_tubing_volume"].toDouble();

    if(formData.contains("rd_skin_factor")) S = formData["rd_skin_factor"].toDouble();

    if(formData.contains("cd_f")) ui->cd_f_lineedit->setText(formData["cd_f"].toString());

    if(formData.contains("cd_kd")) ui->cd_kd_lineedit->setText(formData["cd_kd"].toString());

    if(formData.contains("cd_t_s")) ui->cd_t_s_lineedit->setText(formData["cd_t_s"].toString());

    if(formData.contains("cd_vol_acid")) ui->cd_vol_acid_lineedit->setText(formData["cd_vol_acid"].toString());

    if(formData.contains("cd_vol_pump")) ui->cd_vol_pump_lineedit->setText(formData["cd_vol_pump"].toString());

    if(formData.contains("cd_ro")) ui->cd_ro_lineedit->setText(formData["cd_ro"].toString());

    if(formData.contains("cd_p_safe")) ui->cd_p_safe_lineedit->setText(formData["cd_p_safe"].toString());

    if(formData.contains("cd_t_ci")) ui->cd_t_ci_lineedit->setText(formData["cd_t_ci"].toString());
}
