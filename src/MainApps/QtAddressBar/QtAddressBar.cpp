#include "QtAddressBar.h"
#include "AddressItem.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QStringList>
#include <QResizeEvent>
#include <QFileInfo>
#include <QDir>

#define ROOT_ICON_WIDTH  34

QtAddressBar::QtAddressBar(QWidget *parent) :
    QLineEdit(parent),
    m_pressed(false),
    m_bSelectText(false)
{
    m_pMainLayout = new QHBoxLayout();
    m_pMainLayout->setContentsMargins(1, 1, 1, 1);
    m_pMainLayout->setSpacing(0);
    setLayout(m_pMainLayout);

    m_addressGroup = new QButtonGroup(this);
    m_addressGroup->setExclusive(true);
    m_lastCheckBtn = nullptr;

    connect(m_addressGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onGroupBtnClicked(QAbstractButton*)));

    this->clearFocus();
    setMouseTracking(true);
}

QtAddressBar::~QtAddressBar()
{

}

void QtAddressBar::UpdateCurrentPath(const QString &path)
{
    this->clearFocus();
    clearAddressItem();

    m_currentPath = QString(path).replace("\\", "/");
    setText(QString());

    int itemsWidth = 0;
    int contentWidth = width();

    QStringList itemList = m_currentPath.split("/", QString::SkipEmptyParts);

    //add root icon
    QLabel *rootIcon = new QLabel(this);
    rootIcon->setFixedSize(17, 20);
    rootIcon->setStyleSheet(QString("QLabel{background-image: url(:/res/dir.png);}"));

    m_pMainLayout->addWidget(rootIcon);

    //add path draw control
    AddressItem* root = new AddressItem(QString(), QString(), true, this);
    m_pMainLayout->addWidget(root);
    m_addressGroup->addButton(root, 0);

    contentWidth = contentWidth - ROOT_ICON_WIDTH;

    for(int i=itemList.count()-1; i >= 0; i--)
    {
        QString fullPath;

//        if(itemList[i].isEmpty()) {}

        for(int j=0; j <= i; ++j)
        {
            fullPath +=itemList[j]+"/";
        }
        AddressItem* item = new AddressItem(itemList[i], fullPath, false, this);
        itemsWidth += item->width();
//        qDebug() << "itemsWidth" << itemsWidth;

        m_pMainLayout->insertWidget(2, item);
        connect(item, &AddressItem::SClickPath, this, &QtAddressBar::SCurrentPathChanged);

        if(itemsWidth < contentWidth) {
            item->show();
            m_addressGroup->addButton(item, i);
        }
        else {
            item->hide();
        }
    }

    if(itemsWidth > contentWidth) {
        root->setBackIcon(true);
    }

    m_pMainLayout->addStretch();
}

void QtAddressBar::closeMenu()
{
    if(nullptr != m_lastCheckBtn) {
        m_addressGroup->setExclusive(false);
        m_lastCheckBtn->setChecked(false);
        m_addressGroup->setExclusive(true);

        m_lastCheckBtn = nullptr;
    }
}

void QtAddressBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_pressed = true;
//        if(m_areaPath.contains(e->pos())) {
    }

    QLineEdit::mousePressEvent(event);
}

void QtAddressBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton && m_pressed)
    {
        qDebug() << "click white space";
        m_pressed = false;
        clearAddressItem();

        setText(m_currentPath);

        if(m_bSelectText) {
            deselect();
            m_bSelectText = false;
        }
        else {
            selectAll();
            m_bSelectText = true;
        }
    }

    QLineEdit::mouseReleaseEvent(event);
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

   QLineEdit::mouseMoveEvent(event);
}

void QtAddressBar::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
}

void QtAddressBar::focusOutEvent(QFocusEvent *event)
{
    QFileInfo info(this->text());
    if(info.isDir()) {
        m_currentPath = info.absoluteFilePath();
    }

    UpdateCurrentPath(m_currentPath);

    QLineEdit::focusOutEvent(event);
}

void QtAddressBar::resizeEvent(QResizeEvent *event)
{
    if(m_pMainLayout->count() >= 2) {
        int contentWidth = event->size().width() - ROOT_ICON_WIDTH;
        int itemsWidth = 0;

        foreach (QAbstractButton *button, m_addressGroup->buttons()) {
           m_addressGroup->removeButton(button);
        }
        m_lastCheckBtn = nullptr;

        for (int i=m_pMainLayout->count()-2; i >= 2; i--) //root item(0,1) always show, count()-1 is space item
        {
            QLayoutItem *item = m_pMainLayout->itemAt(i);
            AddressItem *addressItem = qobject_cast<AddressItem *>(item->widget());
            if (addressItem != 0)
            {
                addressItem->hide();
                itemsWidth += addressItem->width();

                if(itemsWidth < contentWidth) {
                    addressItem->show();
                    m_addressGroup->addButton(addressItem, i);
                }
            }
        }

        QLayoutItem *root = m_pMainLayout->itemAt(1);
        AddressItem *rootItem = qobject_cast<AddressItem *>(root->widget());
        if(itemsWidth > contentWidth) {
            rootItem->setBackIcon(true);
        }
        else {
            rootItem->setBackIcon(false);
        }
    }

    clearFocus();

    QLineEdit::resizeEvent(event);
}

void QtAddressBar::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
        QString pathStr = this->text();
        pathStr.replace("\\", "/");
        QFileInfo info(pathStr);

        if(info.isDir()) {
            m_currentPath = info.absoluteFilePath();
        }
        else {
            qDebug() << "not dir";
        }

        UpdateCurrentPath(m_currentPath);
    }

    QLineEdit::keyPressEvent(event);
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

void QtAddressBar::clearAddressItem()
{
    foreach (QAbstractButton *button, m_addressGroup->buttons()) {
       m_addressGroup->removeButton(button);
    }
    m_lastCheckBtn = nullptr;

    QLayoutItem *child;
    while ((child = m_pMainLayout->takeAt(0)) != 0) {
        if(child->widget())
        {
//            delete child->widget();
            child->widget()->deleteLater();
        }
        delete child;
    }
}

