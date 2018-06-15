#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QDirModel>
#include <QStandardItemModel>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(bool isRoot, QWidget *parent = 0);
    ~MenuWidget();

    void updateDirModel(const QString &str);

signals:
    void SClickPath(const QString &path);

private slots:
    void on_listView_clicked(const QModelIndex &index);

private:
    void adjustMenuSize();
    void setRootModel();

private:
    Ui::MenuWidget *ui;

    bool                    m_bRoot;
    QDirModel*              m_pDirModel;
    QStandardItemModel*     m_pRootModel;
};

#endif // MENUWIDGET_H
