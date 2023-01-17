#include "modelforlistofcameras.h"

ModelForListOfCameras::ModelForListOfCameras(QObject *parent)
    : QAbstractListModel(parent)
    , m_modelList(nullptr)
{
}

int ModelForListOfCameras::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 3;
}

QVariant ModelForListOfCameras::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    switch (role) {
    case NumberRole:
        return QVariant(4);
        break;
    case NameRole:
        return QVariant(QStringLiteral("sadASD"));
        break;
    case StatusRole:
        return QVariant("blue");
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
    list[StatusRole] = "status";
    return list;
}
