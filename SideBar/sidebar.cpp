#include "sidebar.h"
#include "ui_sidebar.h"
#include <QDebug>

Sidebar::Sidebar(QWidget *parent, const QString &title) :
    QWidget(parent),
    ui(new Ui::Sidebar) ,
    m_dir(Sidebar::LeftToRight) ,
    m_title(title)
{
    ui->setupUi(this);
    initObjects();
    //initAnimation();
    configLayout();
    connectObjects();

}

Sidebar::~Sidebar()
{
    delete ui;

    if(animation)
        delete animation;

    if(sidebarContainer)
            delete sidebarContainer;
}

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

    sidebarLabel = new SidebarLabel(this);
    sidebarLabel->setSidebarLabelTitle(m_title);
}

void Sidebar::connectObjects()
{
    connect(sidebarLabel , &SidebarLabel::sidebarPositionChanged , this ,[this](const QPoint &newPoint){

        if(m_dir == Sidebar::LeftToRight || m_dir == Sidebar::RightToLeft)
        {
            int currentX = this->pos().x();
            this->move(currentX , mapToParent(newPoint).y());
        }
        else
        {
            int currentY = this->pos().y();
            this->move(mapToParent(newPoint).x() ,currentY );
        }
    });
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
    case Sidebar::LeftToRight:
        ui->widgetLeft->setHidden(true);
        ui->widgetTop->setHidden(true);
        ui->widgetBottom->setHidden(true);
        ui->widgetRight->setHidden(false);

        ui->verticalLayoutRight->addWidget(sidebarLabel);

        sidebarLabel->setSidebarLabelOrientation(SideBarContainer::Vertical);
        sidebarContainer->setContainerOrientation(SideBarContainer::Vertical);
        break;
    case Sidebar::RightToLeft:
        ui->widgetRight->setHidden(true);
        ui->widgetTop->setHidden(true);
        ui->widgetBottom->setHidden(true);

        ui->widgetLeft->setHidden(false);

        ui->verticalLayoutLeft->addWidget(sidebarLabel);

        sidebarLabel->setSidebarLabelOrientation(SideBarContainer::Vertical);
        sidebarContainer->setContainerOrientation(SideBarContainer::Vertical);
        break;
    case Sidebar::DownToUp:
        ui->widgetRight->setHidden(true);
        ui->widgetBottom->setHidden(true);
        ui->widgetLeft->setHidden(true);
        ui->widgetTop->setHidden(false);

        ui->horizontalLayoutBottom->addWidget(sidebarLabel);

        sidebarLabel->setSidebarLabelOrientation(SideBarContainer::Horizontal);
        sidebarContainer->setContainerOrientation(SideBarContainer::Horizontal);
        break;
    case Sidebar::UpToDown:
        ui->widgetRight->setHidden(true);
        ui->widgetTop->setHidden(true);
        ui->widgetLeft->setHidden(true);
        ui->widgetBottom->setHidden(false);

        ui->horizontalLayoutTop->addWidget(sidebarLabel);

        sidebarLabel->setSidebarLabelOrientation(SideBarContainer::Horizontal);
        sidebarContainer->setContainerOrientation(SideBarContainer::Horizontal);
        break;
    }
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
     sidebarLabel->hide();
    }
    else
    {
      sidebarContainer->hide();
      sidebarLabel->show();
      ui->rightExpandBut->setArrowType(Qt::RightArrow);
    }
}

void Sidebar::on_leftExpandBut_clicked(bool checked)
{
    if(checked)
    {
     animation->start(QPropertyAnimation::KeepWhenStopped);
     sidebarContainer->show();

     sidebarLabel->hide();
     ui->leftExpandBut->setArrowType(Qt::RightArrow);
    }
    else
    {
      sidebarContainer->hide();
      sidebarLabel->show();
      ui->leftExpandBut->setArrowType(Qt::LeftArrow);
    }
}

void Sidebar::on_upExpandBut_clicked(bool checked)
{
    if(checked)
    {
     animation->start(QPropertyAnimation::KeepWhenStopped);
     sidebarContainer->show();

     sidebarLabel->hide();
     ui->upExpandBut->setArrowType(Qt::DownArrow);
    }
    else
    {
      sidebarContainer->hide();
      sidebarLabel->show();
      ui->upExpandBut->setArrowType(Qt::UpArrow);
    }
}

void Sidebar::on_downExpandBut_clicked(bool checked)
{
    if(checked)
    {
     animation->start(QPropertyAnimation::KeepWhenStopped);
     sidebarContainer->show();

     sidebarLabel->hide();
     ui->downExpandBut->setArrowType(Qt::UpArrow);
    }
    else
    {
      sidebarContainer->hide();
      sidebarLabel->show();
      ui->downExpandBut->setArrowType(Qt::DownArrow);
    }
}

SidebarLabel::SidebarLabel(QWidget *parent , SideBarContainer::ContainerOrientaion orientation) : QWidget(parent) , m_orientation(orientation)
{
    layout = new QGridLayout(this);
    layout->setContentsMargins( 0 , 0 , 0 , 0);
    layout->setSpacing(0);
    setMouseTracking(true);
}

void SidebarLabel::setSidebarLabelOrientation(SideBarContainer::ContainerOrientaion orientation)
{
    m_orientation = orientation;
}

void SidebarLabel::setSidebarLabelTitle(const QString &title)
{
    m_title = title;
}

QSize SidebarLabel::minimumSizeHint() const
{   if(m_orientation == SideBarContainer::Horizontal)
        return QSize(100 ,12);
    else //Vertical
        return QSize(12 , 100);
}

void SidebarLabel::paintEvent(QPaintEvent *event)
{
    if(m_orientation == SideBarContainer::Horizontal)
        this->setMaximumWidth(100);
     else
        this->setMaximumHeight(100);

    if(m_title  == "")
        this->setHidden(true);

    QPainter p(this);

    QFont fontText(p.font());
    fontText.setFamily("Helvetica Neue");
    fontText.setPointSize(10);
    p.setFont(fontText);
    p.setPen(Qt::darkGray);

    //p.fillRect(rect(), QColor(50, 100, 100));

    QSize size = p.fontMetrics().size(Qt::TextSingleLine, m_title);

    if(m_orientation == SideBarContainer::Vertical)
    {
        p.translate(event->rect().width() /2 - size.width()/4, event->rect().height() /2 + size.height());

        p.rotate(-90);
        p.drawText(QRect( 0 , 0 , (event->rect().width() + size.width()) * 3 ,event->rect().height()), m_title);
    }
    else
        p.drawText(event->rect(), Qt::AlignCenter, m_title);

}

void SidebarLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
       sidebarCurrentPos = event->pos();
       // offset = mapToParent(event->pos());
    }
}

void SidebarLabel::mouseMoveEvent(QMouseEvent *event)
{
    this->setCursor(Qt::OpenHandCursor);

    if(event->buttons() & Qt::LeftButton)
    {
        QPoint diffPos = event->pos() - sidebarCurrentPos;
//        if(m_orientation == SideBarContainer::ContainerOrientaion::Vertical
//                 && ((diffPos.x() <= -2 || diffPos.x() >= 2)))
//            return;
        //parentWidget()->parentWidget()->move(mapToParent(event->pos()) - sidebarCurrentPos);
        emit sidebarPositionChanged(diffPos);
    }

}
