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
    return m_modelList -> items().size();
}

QVariant ModelForListOfCameras::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
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

void ModelForListOfCameras::setModelList(const QStringList &modelList)
{
    if (m_modelList != modelList)
    {
        m_comboList = modelList;
        emit comboListChanged();
        rowCount(modelList.size());
    }
}

Qt::ItemFlags ModelForListOfCameras::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}
