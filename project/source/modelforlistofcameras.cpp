#include "modelforlistofcameras.h"
#include <iostream>

ModelForListOfCameras::ModelForListOfCameras(QObject *parent)
    : QAbstractListModel(parent)

{
    std::cout << "ModelForListOfCameras created" << std::endl;
    //         CameraItem test = {0, QStringLiteral("name"),QStringLiteral("addr"), 1};
    //         m_listOfCameras.append(test);
    //         test.Number = 1;
    //         test.Status = 0;
    //         m_listOfCameras.append(test);
}

int ModelForListOfCameras::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    std::cout << "m_listOfCameras.size(): " << m_listOfCameras.size()<< std::endl;
    // FIXME: Implement me!
    return m_listOfCameras.size();
}

QVariant ModelForListOfCameras::data(const QModelIndex &index, int role) const
{
    std::cout << "data" << std::endl;
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    CameraItem* item = m_listOfCameras.at(index.row());
    switch (role) {
    case NumberRole:
        return QVariant(item->Number);
        break;
    case NameRole:
        return QVariant(item->Name);
        break;
    case AddrRole:
        return QVariant(item->Addr);
        break;
    case StatusRole:
        return QVariant(item->Status);
        break;
    default:
        break;
    }
    return QVariant();
}


bool ModelForListOfCameras::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ModelForListOfCameras::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> ModelForListOfCameras::roleNames() const
{
    QHash<int, QByteArray> list;
    list[NumberRole] = "number";
    list[NameRole] = "partnumber";
    list[AddrRole] = "addr";
    list[StatusRole] = "status";
    return list;
}
void ModelForListOfCameras::addItem(CameraItem* item)
{
    m_listOfCameras.append(item);
}

QVector<CameraItem> ModelForListOfCameras::getDeviceList()
{
    CameraItem test = {0, QStringLiteral("name"),QStringLiteral("addr"), 1};
    return QVariant(test);
}


