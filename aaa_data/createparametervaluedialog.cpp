#include <QDebug>

#include "createparametervaluedialog.h"
#include "ui_createparametervaluedialog.h"

#include "settings.h"

CreateParameterValueDialog::CreateParameterValueDialog(int recommendationFromId, int fieldId, int categoryId, int parameterId, QString fieldKey, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateParameterValueDialog)
{
    ui->setupUi(this);

    currentWidget = 0;

    m_RecommendationFromId = recommendationFromId;

    m_FieldId = fieldId;
    m_CategoryId = categoryId;
    m_ParameterId = parameterId;

    m_FieldKey = fieldKey;

    model = new QSqlQueryModel(this);
    categoryModel = new QSqlQueryModel(this);    

    ui->propertyComboBox->setModel(model);
    ui->categoryComboBox->setModel(categoryModel);

    displayCategoryList();
}

CreateParameterValueDialog::~CreateParameterValueDialog()
{
    delete ui;

    qDebug() << "CreateParameterValue Dialog is destroyed";
}

void CreateParameterValueDialog::acceptCreate()
{
    if(Settings::get()->formMap.contains(m_FieldKey)) Settings::get()->formMap[m_FieldKey]->acceptCreate(m_RecommendationFromId, m_FieldKey);

    accept();
}

void CreateParameterValueDialog::currentIndexChanged(int index)
{   
    if(currentWidget != 0)
    {
        ui->verticalLayout->removeWidget(currentWidget);

        currentWidget->deleteLater();

        currentWidget = 0;
    }

    QModelIndex idIndex = model->index(index, 0);
    QModelIndex keyIndex = model->index(index, 1);

    if(idIndex.isValid()) m_FieldId = idIndex.data().toInt();
    if(keyIndex.isValid())
    {
        m_FieldKey = keyIndex.data().toString();

        if(Settings::get()->formMap.contains(m_FieldKey)) currentWidget = Settings::get()->formMap[m_FieldKey]->display(-1, m_ParameterId, QString(), ui->verticalLayout);
    }

    qDebug() << "CreateParameterValueDialog currentIndexChanged, index = " << index << ", id = " << m_FieldId;
}

void CreateParameterValueDialog::currentCategoryIndexChanged(int index)
{
    QModelIndex categoryIdIndex = categoryModel->index(index, 0);

    if(categoryIdIndex.isValid()) m_CategoryId = categoryIdIndex.data().toInt();

    displayList();

    qDebug() << "CreateParameterValueDialog currentCategoryIndexChanged, index = " << index << ", categoryId = " << m_CategoryId;
}

void CreateParameterValueDialog::displayList()
{
    model->setQuery(QString("select id, key, name_%1 from recommendation_field where category_id=%2 and is_recommendation_field=1").arg(Settings::get()->shortLocale()).arg(m_CategoryId));

    ui->propertyComboBox->setModelColumn(2);

    listDataBind();
}

void CreateParameterValueDialog::displayCategoryList()
{
    categoryModel->setQuery(QString("select id, name_%1 from recommendation_field_category").arg(Settings::get()->shortLocale()));

    ui->categoryComboBox->setModelColumn(1);

    categoryListDataBind();
}

void CreateParameterValueDialog::listDataBind()
{
    for(int i = 0; i < model->rowCount(); i++)
    {
        int id = model->index(i, 0).data().toInt();

        if(m_FieldId == id) ui->propertyComboBox->setCurrentIndex(i);
    }
}

void CreateParameterValueDialog::categoryListDataBind()
{
    for(int i = 0; i < categoryModel->rowCount(); i++)
    {
        int categoryId = categoryModel->index(i, 0).data().toInt();

        if(m_CategoryId == categoryId) ui->categoryComboBox->setCurrentIndex(i);
    }
}

