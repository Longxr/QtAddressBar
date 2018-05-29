#ifndef QTADDRESSBAR_H
#define QTADDRESSBAR_H

#include <QObject>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QButtonGroup>

#include "AddressItem.h"

class QtAddressBar : public QLineEdit
{
    Q_OBJECT

public:
    explicit QtAddressBar(QWidget *parent = 0);
    ~QtAddressBar();

    void UpdateCurrentPath(const QString &path);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

private slots:
    void onGroupBtnClicked(QAbstractButton*);

private:
    bool                m_pressed;
    QString             m_currentPath;
    QButtonGroup*       m_addressGroup;
    QAbstractButton*    m_lastCheckBtn;
    QHBoxLayout*        m_pMainLayout;

};

#endif // QTADDRESSBAR_H
