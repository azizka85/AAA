#ifndef DOUBLEEDITORDELEGATE_H
#define DOUBLEEDITORDELEGATE_H

#include <QItemDelegate>

class DoubleEditorDelegate : public QItemDelegate
{
public:
    DoubleEditorDelegate(QObject* parent);
    ~DoubleEditorDelegate();

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DOUBLEEDITORDELEGATE_H
