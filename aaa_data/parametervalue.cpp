#include <QDebug>
#include <QVBoxLayout>
#include "parametervalue.h"

ParameterValue::ParameterValue(QString queryStr, QString createQueryStr, QString updateQueryStr)
{
    qDebug() << "ParameterValue::ParameterValue - " << queryStr;

    m_QueryStr = queryStr;
    m_CreateQueryStr = createQueryStr;
    m_UpdateQueryStr = updateQueryStr;

    form = 0;
}

ParameterValue::~ParameterValue()
{
    qDebug() << "ParameterValue is destroyed";
}

QWidget* ParameterValue::display(int id, int parameterId, QString recommendation, QVBoxLayout *parent)
{
    if(parent != 0)
    {
        form = new ParameterValueForm(id, parameterId, recommendation, m_QueryStr, m_CreateQueryStr, m_UpdateQueryStr, parent);

        parent->addWidget(form);

        return form;
    }

    return 0;
}

void ParameterValue::acceptCreate(int recommendationFromId, QString fieldKey)
{
    if(form != 0) form->acceptCreate(recommendationFromId, fieldKey);
}

void ParameterValue::acceptEdit()
{
    if(form != 0) form->acceptEdit();
}
