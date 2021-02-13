#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <sidebar.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWidget *ui;
    Sidebar* sidebarLeft;
    Sidebar* sidebarRight;
    Sidebar* sidebarTop;
    Sidebar* sidebarBottom;
};
#endif // MAINWIDGET_H
