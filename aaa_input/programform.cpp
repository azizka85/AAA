#include <QDebug>

#include "programform.h"
#include "ui_programform.h"

ProgramForm::ProgramForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramForm)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->pp_coil_tube_od_lineedit->setValidator(validator);

    ui->pp_coil_tube_length_lineedit->setValidator(validator);
}

ProgramForm::~ProgramForm()
{
    qDebug() << "ProgramForm is destroyed";

    delete ui;
}

void ProgramForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("pp_job_description")) ui->pp_job_description_lineedit->setText(formData["pp_job_description"].toString());

    if(formData.contains("pp_acidizing_technique")) ui->pp_acidizing_technique_lineedit->setText(formData["pp_acidizing_technique"].toString());

    if(formData.contains("pp_design_steps")) ui->pp_design_steps_textedit->setText(formData["pp_design_steps"].toString());

    if(formData.contains("pp_use_diversion")) ui->pp_use_diversion_checkbox->setChecked(formData["pp_use_diversion"].toBool());

    if(formData.contains("pp_diversion_type")) ui->pp_diversion_type_lineedit->setText(formData["pp_diversion_type"].toString());

    if(formData.contains("pp_placement_technique")) ui->pp_placement_technique_lineedit->setText(formData["pp_placement_technique"].toString());

    if(formData.contains("pp_coil_tube_od")) ui->pp_coil_tube_od_lineedit->setText(formData["pp_coil_tube_od"].toString());

    if(formData.contains("pp_coil_tube_length")) ui->pp_coil_tube_length_lineedit->setText(formData["pp_coil_tube_length"].toString());
}

void ProgramForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["pp_job_description"] = ui->pp_job_description_lineedit->text();

    formData["pp_acidizing_technique"] = ui->pp_acidizing_technique_lineedit->text();

    formData["pp_design_steps"] = ui->pp_design_steps_textedit->toPlainText();

    formData["pp_use_diversion"] = ui->pp_use_diversion_checkbox->isChecked();

    formData["pp_diversion_type"] = ui->pp_diversion_type_lineedit->text();

    formData["pp_placement_technique"] = ui->pp_placement_technique_lineedit->text();

    formData["pp_coil_tube_od"] = ui->pp_coil_tube_od_lineedit->text();

    formData["pp_coil_tube_length"] = ui->pp_coil_tube_length_lineedit->text();
}
