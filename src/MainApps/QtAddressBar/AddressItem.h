#ifndef ADDRESSITEM_H
#define ADDRESSITEM_H

#include <QPushButton>
#include <QMenu>

class AddressItem : public QPushButton
{
    Q_OBJECT
public:
    explicit AddressItem(const QString &text, const QString &path, bool bArrow = true, QWidget *parent = 0);
    ~AddressItem();

    void setSubItems(QVector<QString> subItems);
    void setBackIcon(bool flag);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private slots:
    void menuAboutToHide();
    void onClickSubItem();
    void onCheckChanged(bool checked);

private:
    void InitUI();

private:
    bool m_pressed = false;
    bool m_pressedText = false;
    QMenu* m_clickmenu;

    bool m_moveflag = false;

    bool m_bHaveArrow;
    int m_textWidth;
    QFont m_font;

    QString m_path;
    QString m_text;

    QPixmap m_normalIcon;
    QPixmap m_checkedIcon;

    QVector<QString> m_subitems;
};

#endif // ADDRESSITEM_H
