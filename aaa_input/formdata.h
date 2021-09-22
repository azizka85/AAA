#ifndef FORMDATA_H
#define FORMDATA_H

#include <QVariant>
#include <QString>
#include <QMap>
#include <QWidget>

class FormData
{
public:

    FormData(QString title) { m_FirstChildId = -1; m_Title = title; }

    virtual ~FormData() { }

    virtual QWidget* display(QMap<QString, QString>& formMap, QMap<QString, QVariant>& formData) { return 0; }

    virtual void saveFormData(QMap<QString, QVariant>& formData) {  }

    QString title() { return m_Title; }

    void setTitle(QString title) { m_Title = title; }

    int firstChildId() { return m_FirstChildId; }

    void setFirstChildId(int id) { m_FirstChildId = id; }

protected:

    int m_FirstChildId;

    QString m_Title;
};

#endif // FORMDATA_H
