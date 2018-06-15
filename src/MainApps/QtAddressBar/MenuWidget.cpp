#include "MenuWidget.h"
#include "ui_MenuWidget.h"

#include <QStandardPaths>

MenuWidget::MenuWidget(bool isRoot, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget),
    m_bRoot(isRoot)
{
    ui->setupUi(this);

    if(m_bRoot) {
        m_pRootModel = new QStandardItemModel(this);
        ui->listView->setModel(m_pRootModel);
        setRootModel();
    }
    else {
        m_pDirModel = new QDirModel(this);
        m_pDirModel->setReadOnly(false);
        m_pDirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        ui->listView->setModel(m_pDirModel);
    }

//    ui->listView->setItemDelegate(m_Delegate);
    ui->listView->setSpacing(0);
    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setResizeMode(QListView::Adjust);
    ui->listView->setDragEnabled(false);
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::updateDirModel(const QString &path)
{
    QFileInfo info(path);
    if(info.isDir()) {
        m_pDirModel->refresh(m_pDirModel->index(path));
        ui->listView->setRootIndex(m_pDirModel->index(path));
    }
}

void MenuWidget::adjustMenuSize()
{

}

void MenuWidget::setRootModel()
{
    m_pRootModel->clear();

    QStandardItem* item1 = new QStandardItem();
    item1->setData(QIcon(":/res/dir.png"), Qt::DecorationRole);
    item1->setData(tr("Desktop"), Qt::DisplayRole);
    item1->setData(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), Qt::UserRole + 1);
    m_pRootModel->appendRow(item1);

    QStandardItem* item2 = new QStandardItem();
    item2->setData(QIcon(":/res/dir.png"), Qt::DecorationRole);
    item2->setData(tr("Documents"), Qt::DisplayRole);
    item2->setData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), Qt::UserRole + 1);
    m_pRootModel->appendRow(item2);

    QStandardItem* item3 = new QStandardItem();
    item3->setData(QIcon(":/res/dir.png"), Qt::DecorationRole);
    item3->setData(tr("Pictures"), Qt::DisplayRole);
    item3->setData(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), Qt::UserRole + 1);
    m_pRootModel->appendRow(item3);
}

void MenuWidget::on_listView_clicked(const QModelIndex &index)
{
    QString path = index.data(Qt::UserRole + 1).toString();

    emit SClickPath(path);

}
