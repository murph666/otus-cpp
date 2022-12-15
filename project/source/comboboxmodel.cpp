#include "comboboxmodel.h"

ComboBoxModel::ComboBoxModel(QObject *parent) :
    QObject(parent)
{
    //    std::cout << "ComboBoxModel created" << std::endl;
}


const QStringList ComboBoxModel::comboList()
{
    return m_comboList;
}

void ComboBoxModel::setComboList(const QStringList &comboList)
{
    if (m_comboList != comboList)
    {
        m_comboList = comboList;
        emit comboListChanged();
        setCount(comboList.size());
    }

}

int ComboBoxModel::count()
{
    return m_count;
}

void ComboBoxModel::setCount(int cnt)
{
    if (cnt != m_count)
    {
        m_count = cnt;
        emit countChanged();
    }
}

void ComboBoxModel::addElement(const QString &element)
{
    m_comboList.append(element);
    emit comboListChanged();
    setCount(m_comboList.count());
    emit countChanged();
}

void ComboBoxModel::clear(){
    while (m_comboList.count()){
        m_comboList.removeAt(m_comboList.count() - 1);
        setCount(m_comboList.count() - 1);
    }
}

void ComboBoxModel::removeElement(int index)
{
    if (index < m_comboList.count())
    {
        m_comboList.removeAt(index);
        emit comboListChanged();
        setCount(m_comboList.count());
        emit countChanged();
    }
}
