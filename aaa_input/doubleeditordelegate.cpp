#include <QLineEdit>
#include <QDebug>

#include "doubleeditordelegate.h"

DoubleEditorDelegate::DoubleEditorDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

DoubleEditorDelegate::~DoubleEditorDelegate()
{
    qDebug() << "DoubleEditorDelegate is destroyed";
}

QWidget *DoubleEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);

    QRegExp regExp("^0\\.[0-9]+$");

    QRegExpValidator* regValidator = new QRegExpValidator(regExp, parent);

    editor->setValidator(regValidator);

    editor->installEventFilter(const_cast<DoubleEditorDelegate *>(this));

    return editor;
}

void DoubleEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QVariant value = index.data();

    QLineEdit *dsb = static_cast<QLineEdit*>(editor);

    dsb->setText(value.toString());
}

void DoubleEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *dsb = static_cast<QLineEdit*>(editor);

    QString value = dsb->text();

    model->setData(index, value);
}

void DoubleEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
