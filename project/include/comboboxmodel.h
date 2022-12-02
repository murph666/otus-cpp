#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QObject>
#include <QStringList>
#include <iostream>

class ComboBoxModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList comboList READ comboList WRITE setComboList NOTIFY comboListChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    ComboBoxModel(QObject *parent = 0);
    ComboBoxModel(const QStringList &list,int count, QObject *parent = 0);

    const QStringList comboList();

    int count();
    void setCount(int cnt);
    void clear();

    Q_INVOKABLE void removeElement(int index);

signals:
    void comboListChanged();
    void countChanged();

public slots:
    Q_INVOKABLE void addElement(const QString &element);
    void setComboList(const QStringList &comboList);

private:
    QStringList m_comboList;
    int         m_count;
};

#endif // COMBOBOXMODEL_H
