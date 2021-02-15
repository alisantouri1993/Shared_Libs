#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include "sidebarcontainer.h"

namespace Ui {
class Sidebar;
}

class SidebarLabel;

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr ,const QString &title = "");
    ~Sidebar();

    enum Direction {
         RightToLeft ,
         LeftToRight  ,
         UpToDown   ,
         DownToUp
        };

private:
    //void initAnimation();
    void initObjects();
    void connectObjects();
    void configLayout();

public :
    void setSideBarDirection(Sidebar::Direction dir);
    void setSideBarSelection(SideBarContainer::Selection select);
    void repaintNeeded();
    QAction * addAction(const QString &text, const QIcon &icon = QIcon() , bool popupMenuEnabled = false);
    QAction * addMenuAction(QAction *action  ,const QString &text , const QIcon &icon = QIcon());

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_rightExpandBut_clicked(bool checked);
    void on_leftExpandBut_clicked(bool checked);

    void on_upExpandBut_clicked(bool checked);

    void on_downExpandBut_clicked(bool checked);

private:
    Ui::Sidebar *ui;
    SideBarContainer * sidebarContainer;
    QPropertyAnimation *animation;

    Sidebar::Direction m_dir;

    SidebarLabel * sidebarLabel;
    QString m_title = "";
};


class SidebarLabel : public QWidget
{
    Q_OBJECT
public:
    explicit SidebarLabel(QWidget *parent = nullptr , SideBarContainer::ContainerOrientaion orientation = SideBarContainer::Vertical);
    ~SidebarLabel() = default;
public:
    void setSidebarLabelOrientation(SideBarContainer::ContainerOrientaion orientation);
    void setSidebarLabelTitle(const QString &title);
    QSize minimumSizeHint() const;
protected:
  void paintEvent(QPaintEvent *event);
private:
  QString m_title = "";
  QGridLayout * layout;
  SideBarContainer::ContainerOrientaion m_orientation;

};

#endif // SIDEBAR_H
