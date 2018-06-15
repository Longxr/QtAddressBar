#include "AddressItem.h"

#include <QFontMetrics>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>

#define ARROW_WIDTH     17
#define SPACE_WIDTH     8
#define ITEM_HEIGHT     20

AddressItem::AddressItem(const QString &text, const QString &path, bool bArrow, QWidget *parent) :
    QPushButton(parent),
    m_bHaveArrow(bArrow),
    m_path(path),
    m_text(text)
{
    m_font = parent->font();

    if(m_text.isEmpty()) {
        m_textWidth = 0;
        setFixedSize(ARROW_WIDTH, 21);
    }
    else {
        QFontMetrics fm(m_font);
        m_textWidth = fm.width(m_text) + SPACE_WIDTH;
        setFixedSize(m_textWidth + ARROW_WIDTH, 21);
    }

    InitUI();
}

AddressItem::~AddressItem()
{
    delete m_clickmenu;
}

void AddressItem::setBackIcon(bool flag)
{
    if(flag) {
        m_normalIcon = QPixmap(":/res/arrow_back.png");
    }
    else {
        m_normalIcon = QPixmap(":/res/arrow_right.png");
    }
}

void AddressItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if  (m_moveflag)
    {
        painter.setPen(QColor(205, 232, 254));
        painter.fillRect(QRectF(0, 0, m_textWidth+ARROW_WIDTH, ITEM_HEIGHT), QBrush(QColor(229, 243, 254)));
        painter.drawRect(QRectF(0,0, m_textWidth, ITEM_HEIGHT));
        painter.drawRect(QRectF(m_textWidth, 0, ARROW_WIDTH, ITEM_HEIGHT));
    }

    if (m_pressed || isChecked())
    {
        painter.setPen(QColor(153, 209, 255));
        painter.fillRect(QRectF(0, 0, m_textWidth+ARROW_WIDTH, ITEM_HEIGHT), QBrush(QColor(204, 232, 255)));
        painter.drawRect(QRectF(0,0, m_textWidth, ITEM_HEIGHT));
        painter.drawRect(QRectF(m_textWidth, 0, ARROW_WIDTH, ITEM_HEIGHT));

        painter.setPen(QColor(0, 0, 0));
        painter.setFont(m_font);
        painter.drawText(QRectF(1,1, m_textWidth, ITEM_HEIGHT), Qt::AlignCenter, m_text);
        painter.drawPixmap(QRectF(m_textWidth, 0, ARROW_WIDTH, ITEM_HEIGHT), m_checkedIcon, m_checkedIcon.rect());
    }
    else
    {
        painter.setPen(QColor(0, 0, 0));
        painter.setFont(m_font);
        painter.drawText(QRectF(0,0, m_textWidth, ITEM_HEIGHT), Qt::AlignCenter, m_text);
        painter.drawPixmap(QRectF(m_textWidth, 0, ARROW_WIDTH, ITEM_HEIGHT), m_normalIcon, m_normalIcon.rect());
    }

}

void AddressItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && hitButton(event->pos())) {
        m_pressed = true;

        if(QRectF(0,0, m_textWidth, ITEM_HEIGHT).contains(event->pos())){
            m_pressedText = true;

        }
        else if(QRectF(m_textWidth, 0, ARROW_WIDTH, ITEM_HEIGHT).contains(event->pos())) {
//            setChecked(!isChecked());
            update();
            return QPushButton::mousePressEvent(event);
        }

        update();
    }
}

void AddressItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(m_pressedText) {
            qDebug() << "clicked item";
            emit SClickPath(m_path);
        }

        m_pressedText = false;
        m_pressed = false;

        update();

        return QPushButton::mouseReleaseEvent(event);
    }
}

//void AddressItem::mouseMoveEvent(QMouseEvent *event)
//{
//    if(hitButton(event->pos())) {
//        m_moveflag = true;
//    }
//    update();
//}

void AddressItem::enterEvent(QEvent *)
{
    m_moveflag = true;
    update();
}

void AddressItem::leaveEvent(QEvent *)
{
    m_moveflag = false;
//    m_clickmenu->hide();
    update();
}

bool AddressItem::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == m_clickmenu)
//    {
//        QEvent::Type eType = event->type();
//        if(eType == QEvent::FocusOut)
//        {
//            m_clickmenu->hide();
//            return false;
//        }
//    }

    return QWidget::eventFilter(watched, event);
}

//void AddressItem::mouseMoveEvent(QMouseEvent *event)
//{
//    if(rect().contains(event->pos())) {
//        m_moveflag = true;
//    }
//    else {
//        m_moveflag = false;
//    }

//    update();
//}

void AddressItem::menuAboutToHide()
{
    m_moveflag = false;
    m_pressed = false;
}

void AddressItem::onClickMenuItem()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QString actionPath = m_path + action->text();

    qDebug() << "clicked menu";
    emit SClickPath(actionPath);
}

void AddressItem::onCheckChanged(bool checked)
{
    update();

    if (checked)
    {
        if(!m_clickmenu->isVisible()) {
            QPoint GlobalPoint(this->mapToGlobal(QPoint(0,0)));
            GlobalPoint.setX(GlobalPoint.x() + ARROW_WIDTH+m_textWidth - 30);
            GlobalPoint.setY(GlobalPoint.y() + ITEM_HEIGHT);
            m_clickmenu->move(GlobalPoint);
            //menu->move(cursor().pos());
            m_clickmenu->show();
        }
    }
    else{
        m_clickmenu->close();
    }
}

void AddressItem::InitUI()
{
    m_normalIcon = QPixmap(":/res/arrow_right.png");
    m_checkedIcon = QPixmap(":/res/arrow_down.png");

    m_clickmenu = new QMenu(this);
    m_clickmenu->setWindowFlags(Qt::ToolTip);
    m_clickmenu->installEventFilter(this);
//    setAttribute(Qt::WA_TransparentForMouseEvents);
    connect(m_clickmenu, SIGNAL(aboutToHide()), this, SLOT(menuAboutToHide()));

    m_clickmenu->clear();
    QDir dir(m_path);
    dir.setFilter(/*QDir::Files | QDir::Hidden | */QDir::NoSymLinks | QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);
    QStringList list = dir.entryList();
    foreach(QString str, list) {
        QAction* strAc = new QAction(QIcon(":/res/dir.png"), str, m_clickmenu);
        connect(strAc, &QAction::triggered, this, &AddressItem::onClickMenuItem);
        m_clickmenu->addAction(strAc);
    }

    m_clickmenu->setStyleSheet("QMenu {background-color:rgb(242,242,242); border: 1px solid rgb(100,100,100);}\
                     QMenu::item {font-size: 9pt; color: rgb(0,0,0); padding:4px 20px 4px 20px;margin:1px 2px;}\
                     QMenu::item:selected { background-color:rgb(196,222,244);}");

    setMouseTracking(true);
    setCheckable(true);
    connect(this, &AddressItem::toggled, this, &AddressItem::onCheckChanged);
}
