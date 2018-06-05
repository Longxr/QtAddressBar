#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "FileSystemModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotShowChild(const QModelIndex &index);
    void slotSelectCurrent(const QModelIndex &index);
    void slotCurrentPathChanged(const QString &path);

    void on_pushButton_clicked();

private:
    void InitUI();

    Ui::MainWindow *ui;

    QString             m_currentPath;
    FileSystemModel*   m_pFileSystemModel;
};

#endif // MAINWINDOW_H
