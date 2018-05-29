#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QFileSystemModel>

class FileSystemModel : public QFileSystemModel
{
    Q_OBJECT

public:
    explicit FileSystemModel(QObject *parent = 0);
    ~FileSystemModel();

    virtual QVariant data(const QModelIndex &index, int role) const;
//    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // FILESYSTEMMODEL_H
