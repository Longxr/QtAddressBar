#include "FileSystemModel.h"

#include <QFont>

FileSystemModel::FileSystemModel(QObject *parent) :
    QFileSystemModel(parent)
{

}

FileSystemModel::~FileSystemModel()
{

}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    switch(role){
    case Qt::FontRole:{
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        return font;
    }

    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);

    default:
        return QFileSystemModel::data(index, role);
    }

    return QFileSystemModel::data(index, role);
}
