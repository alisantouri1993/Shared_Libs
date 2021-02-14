#ifndef SIDEBARCONTAINER_H
#define SIDEBARCONTAINER_H

#include <QAction>
#include <QWidget>

class SideBarContainer : public QWidget
{
    Q_OBJECT
public:
    enum ContainerOrientaion {
         Vertical ,
         Horizontal
    };

    enum Selection {
        Single ,
        Multiple
    };
public:
    explicit SideBarContainer(QWidget *parent = nullptr);
    QAction *addAction(const QString &text, const QIcon &icon = QIcon() , bool popupMenuEnabled = false);
    QAction *addMenuAction(const QString &text, QAction *action , const QIcon &icon = QIcon());
    void setSideBarSelection(SideBarContainer::Selection select);
    QSize minimumSizeHint() const;
    void setContainerOrientation(SideBarContainer::ContainerOrientaion orientation);

signals:

protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void leaveEvent(QEvent *event);

  QAction *actionAt(const QPoint &at);

private:
  QList<QAction *> mActions;

  QAction *mCheckedAction;
  QAction *mOverAction;

  SideBarContainer::ContainerOrientaion m_cOrientation;
  SideBarContainer::Selection m_select;

  QMap<QAction* , QMenu*> actMenuMap;
};

#endif // SIDEBARCONTAINER_H
