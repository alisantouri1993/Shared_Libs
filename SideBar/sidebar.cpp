#include "sidebar.h"
#include "ui_sidebar.h"
#include <QDebug>

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar) ,
    m_dir(Sidebar::Right)
{
    ui->setupUi(this);
    initObjects();
    //initAnimation();
    connectObjects();

    configLayout();
}

Sidebar::~Sidebar()
{
    delete ui;

    if(animation)
        delete animation;

    if(sidebarContainer)
            delete sidebarContainer;
}

//void Sidebar::initAnimation()
//{
//    QGraphicsOpacityEffect* fade_effect = new QGraphicsOpacityEffect(this);
//    sidebarContainer->setGraphicsEffect(fade_effect);
//    //ui->widgetContainer->setGraphicsEffect(fade_effect);
//    animation = new QPropertyAnimation(fade_effect, "opacity");
//    animation->setEasingCurve(QEasingCurve::InOutQuad);
//    animation->setDuration(1000);
//    animation->setStartValue(0.01);
//    animation->setEndValue(1.0);
//}

void Sidebar::initObjects()
{
    sidebarContainer = new SideBarContainer(this);
    ui->containerGridLayout->addWidget(sidebarContainer);

    sidebarContainer->hide();

    QGraphicsOpacityEffect* fade_effect = new QGraphicsOpacityEffect(this);
    sidebarContainer->setGraphicsEffect(fade_effect);
    //ui->widgetContainer->setGraphicsEffect(fade_effect);
    animation = new QPropertyAnimation(fade_effect, "opacity");
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setDuration(1000);
    animation->setStartValue(0.01);
    animation->setEndValue(1.0);
}

void Sidebar::connectObjects()
{
}

void Sidebar::setSideBarDirection(Sidebar::Direction dir)
{
    m_dir = dir;

    configLayout();
}

void Sidebar::setSideBarSelection(SideBarContainer::Selection select)
{
    sidebarContainer->setSideBarSelection(select);
}

void Sidebar::configLayout()
{
    switch (m_dir) {
    case Sidebar::Right:
        ui->widgetLeft->setHidden(true);
        ui->widgetTop->setHidden(true);
        ui->widgetBottom->setHidden(true);

        ui->widgetRight->setHidden(false);

        sidebarContainer->setContainerOrientation(SideBarContainer::Vertical);
        break;
    case Sidebar::Left:
        ui->widgetRight->setHidden(true);
        ui->widgetTop->setHidden(true);
        ui->widgetBottom->setHidden(true);

        ui->widgetLeft->setHidden(false);

        sidebarContainer->setContainerOrientation(SideBarContainer::Vertical);
        break;
    case Sidebar::Up:
        ui->widgetRight->setHidden(true);
        ui->widgetBottom->setHidden(true);
        ui->widgetLeft->setHidden(true);

        ui->widgetTop->setHidden(false);

        sidebarContainer->setContainerOrientation(SideBarContainer::Horizontal);
        break;
    case Sidebar::Down:
        ui->widgetRight->setHidden(true);
        ui->widgetTop->setHidden(true);
        ui->widgetLeft->setHidden(true);

        ui->widgetBottom->setHidden(false);

        sidebarContainer->setContainerOrientation(SideBarContainer::Horizontal);
        break;
    }

//    sidebarContainer->addAction("Map" ,QIcon(":/Images/Images/maps.png"));
//    sidebarContainer->addAction("PPI" ,QIcon(":/Images/Images/ppi.png"));

//    sidebarContainer->addAction("Map_2" ,QIcon(":/Images/Images/maps.png"));
//    sidebarContainer->addAction("PPI_2" ,QIcon(":/Images/Images/ppi.png"));
}

void Sidebar::repaintNeeded()
{
    sidebarContainer->repaint();
    update();
}

QAction *Sidebar::addAction(const QString &text, const QIcon &icon, bool popupMenuEnabled)
{
    return sidebarContainer->addAction(text ,icon ,popupMenuEnabled);
}

QAction *Sidebar::addMenuAction(QAction *action  ,const QString &text ,const QIcon &icon)
{
    return sidebarContainer->addMenuAction(text , action ,icon);
}

void Sidebar::resizeEvent(QResizeEvent *event)
{
    update();
    QWidget::resizeEvent(event);
}

void Sidebar::on_rightExpandBut_clicked(bool checked)
{
    if(checked)
    {
     animation->start(QPropertyAnimation::KeepWhenStopped);
     sidebarContainer->show();

     ui->rightExpandBut->setArrowType(Qt::LeftArrow);
    }
    else
    {
      sidebarContainer->hide();
      ui->rightExpandBut->setArrowType(Qt::RightArrow);
    }
}

void Sidebar::on_leftExpandBut_clicked(bool checked)
{
    if(checked)
    {
     animation->start(QPropertyAnimation::KeepWhenStopped);
     sidebarContainer->show();

     ui->leftExpandBut->setArrowType(Qt::RightArrow);
    }
    else
    {
      sidebarContainer->hide();
      ui->leftExpandBut->setArrowType(Qt::LeftArrow);
    }
}

void Sidebar::on_upExpandBut_clicked(bool checked)
{
    if(checked)
    {
     animation->start(QPropertyAnimation::KeepWhenStopped);
     sidebarContainer->show();

     ui->upExpandBut->setArrowType(Qt::DownArrow);
    }
    else
    {
      sidebarContainer->hide();
      ui->upExpandBut->setArrowType(Qt::UpArrow);
    }
}

void Sidebar::on_downExpandBut_clicked(bool checked)
{
    if(checked)
    {
     animation->start(QPropertyAnimation::KeepWhenStopped);
     sidebarContainer->show();

     ui->downExpandBut->setArrowType(Qt::UpArrow);
    }
    else
    {
      sidebarContainer->hide();
      ui->downExpandBut->setArrowType(Qt::DownArrow);
    }
}
