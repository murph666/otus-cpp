#ifndef MODELFORLISTOFCAMERAS_H
#define MODELFORLISTOFCAMERAS_H

#include <QAbstractListModel>

struct CameraItem
{
    int Number;
    QString Name;
    QString Addr;
    int Status;
};

class ModelForListOfCameras : public QAbstractListModel
{
    Q_OBJECT
//    Q_PROPERTY(ModelForListOfCameras *list READ list WRITE setList)

public:
    explicit ModelForListOfCameras(QObject *parent = nullptr);

    enum{
        NumberRole,
        NameRole,
        AddrRole,
        StatusRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVector<CameraItem> items();

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;


private:
    QVector<CameraItem>     m_listOfCameras;
};

#endif // MODELFORLISTOFCAMERAS_H
