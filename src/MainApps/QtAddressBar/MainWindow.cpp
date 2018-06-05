#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUI();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotShowChild(const QModelIndex &index)
{
    QString path = m_pFileSystemModel->fileInfo(index).absoluteFilePath();
    qDebug() << "path:" << path;

    if(m_pFileSystemModel->fileInfo(index).isDir()) {
        m_currentPath = path;
        ui->addressbar->setText(path);

        ui->tableView->setRootIndex(m_pFileSystemModel->index(m_currentPath));
        ui->tableView->clearSelection();
        ui->tableView->scrollToTop();
    }
    else
    {
#ifdef _WIN32
        path.replace("/","\\");
#endif
        QProcess::startDetached("explorer "+path);
    }
}

void MainWindow::slotSelectCurrent(const QModelIndex &index)
{

}

void MainWindow::slotCurrentPathChanged(const QString &path)
{
    m_currentPath = path;
    m_pFileSystemModel->setRootPath(m_currentPath);

    ui->tableView->setRootIndex(m_pFileSystemModel->index(m_currentPath));
    ui->tableView->scrollToTop();

    ui->addressbar->UpdateCurrentPath(path);
}

void MainWindow::InitUI()
{
    m_currentPath = QString("Z:/QtWorkspace/trunk/PackageMaker_SetupSkin/SetupScripts/classroomcloud");
    m_pFileSystemModel = new FileSystemModel(this);
    m_pFileSystemModel->setRootPath(m_currentPath);
    ui->addressbar->setText(m_currentPath);

    ui->tableView->setModel(m_pFileSystemModel);
    ui->tableView->setRootIndex(m_pFileSystemModel->index(m_currentPath));
    ui->tableView->scrollToTop();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    ui->tableView->setShowGrid(false);  // disable the table grid.
    ui->tableView->verticalHeader()->setDefaultSectionSize(25);  // set row height.
    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->setFrameShape(QFrame::NoFrame);

    connect(ui->tableView, &QTableView::doubleClicked, this, slotShowChild);
    connect(ui->tableView, &QTableView::clicked, this, slotSelectCurrent);

    connect(ui->addressbar, &QtAddressBar::SCurrentPathChanged, this, slotCurrentPathChanged);
}

void MainWindow::on_pushButton_clicked()
{
    m_currentPath = QString("Z:/QtWorkspace/trunk/PackageMaker_SetupSkin/SetupScripts/classroomcloud");
    ui->addressbar->UpdateCurrentPath(m_currentPath);
}
