#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDirModel>
#include <QCompleter>

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

    void onCompleterChoosed(const QString&);
    void onTextChanged(const QString&);
    void on_pushButton_clicked();

protected:
    bool event(QEvent *);
    bool eventFilter(QObject *, QEvent *);

private:
    void InitUI();

    Ui::MainWindow *ui;

    QString             m_currentPath;
    FileSystemModel*    m_pFileSystemModel;

    QCompleter*         m_pCompleter;
    QDirModel*          m_pCompleterModel;
    QString             m_completerDir;
};

#endif // MAINWINDOW_H
