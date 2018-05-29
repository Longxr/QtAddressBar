#include "QtAddressBar.h"
#include "AddressItem.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QLabel>

QtAddressBar::QtAddressBar(QWidget *parent) :
    QLineEdit(parent),
    m_pressed(false)
{
    m_pMainLayout = new QHBoxLayout();
    m_pMainLayout->setContentsMargins(1, 1, 1, 1);
    m_pMainLayout->setSpacing(0);
    setLayout(m_pMainLayout);

    m_addressGroup = new QButtonGroup(this);
    m_addressGroup->setExclusive(true);
    m_lastCheckBtn = nullptr;

    connect(m_addressGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onGroupBtnClicked(QAbstractButton*)));

    setMouseTracking(true);
}

QtAddressBar::~QtAddressBar()
{

}

void QtAddressBar::UpdateCurrentPath(const QString &path)
{
    m_currentPath = path;

    for(int i = m_pMainLayout->count()-1; i >= 0; i--) {
        QWidget* t = m_pMainLayout->itemAt(i)->widget();
        m_pMainLayout->removeWidget(t);
        t->deleteLater();
    }

    foreach (QAbstractButton *button, m_addressGroup->buttons()) {
       m_addressGroup->removeButton(button);
    }
    int itemsWidth = 0;
    int contentWidth = width();

    QStringList itemList = m_currentPath.split("\\");

    //add parent icon
    QLabel *rootIcon = new QLabel(this);
    rootIcon->setFixedSize(17, 20);
    rootIcon->setStyleSheet(QString("QLabel{background-image: url(:/res/dir.png);}"));

    m_pMainLayout->addWidget(rootIcon);

    //add path draw control
    AddressItem* root = new AddressItem(QString(), QString(), true, this);
    m_pMainLayout->addWidget(root);
    m_addressGroup->addButton(root, 0);

    contentWidth = contentWidth - rootIcon->width() - root->width();

    for(int i=itemList.count()-1; i >= 0; i--)
    {
        QString fullPath;
        for(int j=0; j <= i; ++j)
        {
            fullPath +=itemList[j]+"\\";
        }
        AddressItem* item = new AddressItem(itemList[i], fullPath, true, this);
        itemsWidth += item->width();
        qDebug() << "itemsWidth" << itemsWidth;

        if(itemsWidth < contentWidth) {
            m_pMainLayout->insertWidget(2, item);
            m_addressGroup->addButton(item, i);
        }
        else {
            break;
        }
    }

    if(itemsWidth > contentWidth) {
        root->setBackIcon(true);
    }

    m_pMainLayout->addStretch();
}

void QtAddressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QColor(217, 217, 217));
    painter.drawRect(QRect(0, 0, this->width()-1, this->height()-1));
}

void QtAddressBar::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        m_pressed = true;
//        if(m_areaPath.contains(e->pos())) {
    }
}

void QtAddressBar::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton && m_pressed)
    {
        m_pressed = false;

//        if(m_areaPath.contains(e->pos())){

//        emit SClicked();

    }
}

void QtAddressBar::mouseMoveEvent(QMouseEvent *event)
{
   if(0 != m_addressGroup->checkedButton()) {
       foreach (QAbstractButton *button, m_addressGroup->buttons()) {
          if(button->geometry().contains(event->pos()) && m_addressGroup->checkedButton() != button) {
              AddressItem * btn = qobject_cast<AddressItem *>(button);
              btn->setChecked(true);
              m_lastCheckBtn = btn;
//              btn->showMenu();
          }
       }
   }
}

void QtAddressBar::onGroupBtnClicked(QAbstractButton *button)
{
    if(button == m_lastCheckBtn) {
        m_addressGroup->setExclusive(false);
        button->setChecked(false);
        m_addressGroup->setExclusive(true);

        m_lastCheckBtn = nullptr;
    }
    else {
        m_lastCheckBtn = button;
    }

}

