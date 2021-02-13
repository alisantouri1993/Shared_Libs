#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include "sidebarcontainer.h"

namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);
    ~Sidebar();

    enum Direction {
         Right ,
         Left  ,
         Up   ,
         Down
        };
private:
    //void initAnimation();
    void initObjects();
    void connectObjects();
    void configLayout();

public :
    void setSideBarDirection(Sidebar::Direction dir);
    void repaintNeeded();
    QAction * addAction(const QString &text, const QIcon &icon = QIcon());

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
};

#endif // SIDEBAR_H
