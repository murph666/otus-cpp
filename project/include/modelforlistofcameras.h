#ifndef MODELFORLISTOFCAMERAS_H
#define MODELFORLISTOFCAMERAS_H

#include <QAbstractListModel>

class ModelForListOfCameras : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ModelForListOfCameras *list READ list WRITE setList)

public:
    explicit ModelForListOfCameras(QObject *parent = nullptr);

    enum{
        NumberRole,
        NameRole,
        StatusRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    ModelForListOfCameras *list() const;

    Qt::ItemFlags flags(const QModelIndex& index) const override;


private:
    QStringList *m_modelList;
};

#endif // MODELFORLISTOFCAMERAS_H
