#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    sidebarLeft = new Sidebar(this);
    auto map = sidebarLeft->addAction("Map" ,QIcon(":/Images/Images/maps.png"));
    connect(map,&QAction::triggered , this , [](bool ){
        qDebug() << "Map Selected";
    });
    auto ppi = sidebarLeft->addAction("PPI" ,QIcon(":/Images/Images/ppi.png"));
    connect(ppi,&QAction::triggered , this , [](bool ){
        qDebug() << "PPI Selected";
    });
    ui->horizontalLayout->addWidget(sidebarLeft);

//    sidebarRight = new Sidebar(this);
//    sidebarRight->setSideBarDirection(Sidebar::Left);
//    sidebarRight->configLayout();
//    ui->horizontalLayout_2->addWidget(sidebarRight);

//    sidebarTop = new Sidebar(this);
//    sidebarTop->setSideBarDirection(Sidebar::Down);
//    sidebarTop->configLayout();
//    ui->horizontalLayout_3->addWidget(sidebarTop);

//    sidebarBottom = new Sidebar(this);
//    sidebarBottom->setSideBarDirection(Sidebar::Up);
//    sidebarBottom->configLayout();
//    ui->horizontalLayout_4->addWidget(sidebarBottom);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete sidebarLeft;
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    sidebarLeft->repaintNeeded();
//    sidebarRight->repaintAllWidgets();
//    sidebarTop->repaintAllWidgets();
//    sidebarBottom->repaintAllWidgets();

}

