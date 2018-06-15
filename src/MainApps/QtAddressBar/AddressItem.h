#ifndef ADDRESSITEM_H
#define ADDRESSITEM_H

#include <QPushButton>
#include <QMenu>

#include "MenuWidget.h"

class AddressItem : public QPushButton
{
    Q_OBJECT
public:
    explicit AddressItem(const QString &text, const QString &path, bool isRoot = true, QWidget *parent = 0);
    ~AddressItem();

    void setBackIcon(bool flag);

signals:
    void SClickPath(const QString &path);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private slots:
    void menuAboutToHide();
    void onClickMenuItem();
    void onCheckChanged(bool checked);

private:
    void InitUI();

private:
    bool        m_pressed;
    bool        m_pressedText;
    bool        m_moveflag;
    bool        m_bRoot;

    QMenu*      m_clickmenu;
    MenuWidget* m_pMenuWidget;

    int         m_textWidth;
    QFont       m_font;

    QString     m_path;
    QString     m_text;

    QPixmap     m_normalIcon;
    QPixmap     m_checkedIcon;
};

#endif // ADDRESSITEM_H
