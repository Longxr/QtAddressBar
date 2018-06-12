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

signals:
    void SCurrentPathChanged(const QString &path);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    void resizeEvent(QResizeEvent* size);


private slots:
    void onGroupBtnClicked(QAbstractButton*);

private:
    void clearAddressItem();

private:
    bool                m_pressed;
    bool                m_bSelectText;
    bool                m_bInputMode;
    QString             m_currentPath;
    QButtonGroup*       m_addressGroup;
    QAbstractButton*    m_lastCheckBtn;
    QHBoxLayout*        m_pMainLayout;
};

#endif // QTADDRESSBAR_H
