#include <QDebug>

#include "rangeparametervalue.h"

RangeParameterValue::RangeParameterValue(double rangeMin, double rangeMax, int decimals, QString queryStr, QString createQueryStr, QString createParameterQueryStr, QString updateQueryStr, QString updateParameterQueryStr) :
    ParameterValue(queryStr, createQueryStr, updateQueryStr)
{
    m_RangeMin = rangeMin;
    m_RangeMax = rangeMax;

    m_Decimals = decimals;

    m_QueryStr = queryStr;
    m_CreateQueryStr = createQueryStr;
    m_CreateParameterQueryStr = createParameterQueryStr;
    m_UpdateQueryStr = updateQueryStr;
    m_UpdateParameterQueryStr = updateParameterQueryStr;

    form = 0;
}

RangeParameterValue::~RangeParameterValue()
{
    qDebug() << "RangeParameterValue is destroyed";
}

QWidget *RangeParameterValue::display(int id, int parameterId, QString recommendation, QVBoxLayout *parent)
{
    qDebug() << "RangeParameterValue::display - " << m_QueryStr;

    if(parent != 0)
    {
        form = new RangeParameterValueForm(m_RangeMin, m_RangeMax, m_Decimals, id, parameterId, recommendation, m_QueryStr, m_CreateQueryStr, m_CreateParameterQueryStr, m_UpdateQueryStr, m_UpdateParameterQueryStr, parent);

        parent->addWidget(form);

        return form;
    }

    return 0;
}

void RangeParameterValue::acceptCreate(int recommendationFromId, QString fieldKey)
{
    if(form != 0) form->acceptCreate(recommendationFromId, fieldKey);
}

void RangeParameterValue::acceptEdit()
{
    if(form != 0) form->acceptEdit();
}
