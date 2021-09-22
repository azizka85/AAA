#include <QDebug>

#include "picklingform.h"
#include "ui_picklingform.h"

PicklingForm::PicklingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicklingForm)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(this);

    validator->setLocale(QLocale(QLocale::English));

    ui->pa_density_lineedit->setValidator(validator);

    additivesModel = new UpdateModel(0, 2, this);

    ui->pa_additives_tableview->setModel(additivesModel);

    doubleDelegate = new DoubleEditorDelegate(this);
}

PicklingForm::~PicklingForm()
{
    qDebug() << "PicklingForm is destroyed";

    delete ui;
}

void PicklingForm::display(QMap<QString, QString> &formMap, QMap<QString, QVariant> &formData)
{
    if(formData.contains("pa_additives")) additivesModel->setUpdateData(formData["pa_additives"].toMap());

    if(formData.contains("pa_density")) ui->pa_density_lineedit->setText(formData["pa_density"].toString());

    if(formData.contains("pa_displaced_by")) ui->pa_displaced_by_lineedit->setText(formData["pa_displaced_by"].toString());

    additivesModel->setQuery("select id, name_en, null from acid_type");

    additivesModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    additivesModel->setHeaderData(2, Qt::Horizontal, tr("Value"));

    ui->pa_additives_tableview->setColumnHidden(0, true);

    ui->pa_additives_tableview->setColumnWidth(1, 300);
    ui->pa_additives_tableview->setColumnWidth(2, 300);

    ui->pa_additives_tableview->setItemDelegateForColumn(2, doubleDelegate);
}

void PicklingForm::saveFormData(QMap<QString, QVariant> &formData)
{
    formData["pa_density"] = ui->pa_density_lineedit->text();

    formData["pa_displaced_by"] = ui->pa_displaced_by_lineedit->text();

    formData["pa_additives"] = additivesModel->updateData();
}
