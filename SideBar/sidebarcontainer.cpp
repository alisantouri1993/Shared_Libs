#include "sidebarcontainer.h"

#include <QDebug>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QMenu>

#define action_height 60
#define action_width  50
#define container_margin 30

SideBarContainer::SideBarContainer(QWidget *parent) : QWidget(parent) , mCheckedAction(nullptr), mOverAction(nullptr) , m_cOrientation(Vertical) , m_select(Single)
{
    setMouseTracking(true);
}

void SideBarContainer::paintEvent(QPaintEvent *event) {
  QPainter p(this);

  QFont fontText(p.font());
  fontText.setFamily("Helvetica Neue");
  fontText.setPointSize(7);
  p.setFont(fontText);

  int action_x = container_margin/2;
  int action_y = container_margin/2;
  int action_index = 0;
  p.fillRect(rect(), QColor(100, 100, 100));
  for (auto action : mActions) {

    QRect actionRect = rect();
    if(m_cOrientation == Vertical)
        actionRect = QRect(0 , action_y, event->rect().width(), action_height);
    else
        actionRect = QRect(action_x , 0 , action_width , event->rect().height());

    if (action->isChecked()) {
      p.fillRect(actionRect, QColor(35, 35, 35));
    }

    if (action == mOverAction) {
      p.fillRect(actionRect, QColor(150, 150, 150));
    }

    p.setPen(QColor(255, 255, 255));
    QSize size = p.fontMetrics().size(Qt::TextSingleLine, action->text());

    QRect actionTextRect = rect();
    if(m_cOrientation == Vertical){
        actionTextRect = QRect(QPoint(actionRect.width() / 2 - size.width() / 2,
                                actionRect.bottom() - size.height() - 5),
                         size);
    }
    else
    {
        //int action_index = action_x/actionRect.width();
        //qDebug() <<action_index;
        actionTextRect = QRect(QPoint((container_margin/2 + (container_margin/3 * action_index) + (action_index * actionRect.width() + actionRect.width() / 2))- size.width() / 2,
                                actionRect.bottom() - size.height() - 5),
                                 size);
    }
    p.drawText(actionTextRect, Qt::AlignCenter, action->text());

    QRect actionIconRect = rect();
    if(m_cOrientation == Vertical)
    {
        actionIconRect = QRect(0, action_y + 10, actionRect.width(),
                         actionRect.height() - 2 * actionTextRect.height() -
                             10);
    }
    else
    {
        actionIconRect = QRect(action_x, 10, actionRect.width(),
                             actionRect.height() - 2 * actionTextRect.height() -
                                 10);
    }
    QIcon actionIcon(action->icon());
    actionIcon.paint(&p, actionIconRect);

    if(m_cOrientation == Vertical)
        action_y += actionRect.height() + container_margin/3;
    else
        action_x += actionRect.width() + container_margin/3;
    action_index++;
  }
}

QSize SideBarContainer::minimumSizeHint() const {
    if (m_cOrientation == Vertical)
        return QSize(action_height + (container_margin)/2 ,(action_height + container_margin) * (mActions.size()) );
        //return (action_height + 30) * QSize(1, mActions.size());
    else
        return (action_width + (container_margin)/2) * QSize(mActions.size(), 1);
}

void SideBarContainer::setContainerOrientation(SideBarContainer::ContainerOrientaion orientation)
{
    m_cOrientation = orientation;
}

//void SideBarContainer::addAction(QAction *action) {
//  mActions.push_back(action);
//  action->setCheckable(true);
//  update();
//}

QAction *SideBarContainer::addAction(const QString &text, const QIcon &icon, bool popupMenuEnabled) {
  QAction *action = new QAction(icon, text, this);
  action->setCheckable(true);
  mActions.push_back(action);

  if(m_cOrientation == Vertical)
    setMaximumHeight(action_height * mActions.size() +  container_margin + (container_margin/3) * (mActions.size() - 1) );
  else
    setMaximumWidth(action_width * mActions.size() + (container_margin/3) * (mActions.size() - 1) + container_margin );

  if(popupMenuEnabled)
  {
      QMenu *menu = new QMenu(this);
      actMenuMap.insert(action , menu);
  }

  update();
  return action;
}

QAction *SideBarContainer::addMenuAction(const QString &text, QAction *action, const QIcon &icon)
{
    if(actMenuMap.find(action) != actMenuMap.end())
        return actMenuMap[action]->addAction(icon ,text);
    else
        return nullptr;
}

void SideBarContainer::setSideBarSelection(SideBarContainer::Selection select)
{
    m_select = select;
}

void SideBarContainer::mousePressEvent(QMouseEvent *event) {
  QAction *tempAction = actionAt(event->pos());

  if(event->button() == Qt::RightButton)
  {
      if(actMenuMap.find(tempAction) != actMenuMap.end())
      {
          QPoint mousePos = QCursor::pos();
          actMenuMap[tempAction]->popup(QPoint(mousePos.x() , mousePos.y() + 30));
      }
  }
  else
  {
      if (tempAction == nullptr)
          return;

      if(m_select == SideBarContainer::Single && tempAction->isChecked())
          return;

      if(m_select == SideBarContainer::Single)
      {
          if (mCheckedAction)
              mCheckedAction->setChecked(false);
          if (mOverAction == tempAction)
              mOverAction = nullptr;
          mCheckedAction = tempAction;
          tempAction->setChecked(true);
      }

      else
      {
          if (mOverAction == tempAction)
              mOverAction = nullptr;
          tempAction->setChecked(!tempAction->isChecked());
      }
      emit tempAction->triggered(tempAction->isChecked());
  }

  update();
  QWidget::mousePressEvent(event);
}

void SideBarContainer::mouseMoveEvent(QMouseEvent *event) {
  QAction *tempAction = actionAt(event->pos());
  if (tempAction == nullptr) {
    mOverAction = nullptr;
    update();
    return;
  }
  if (tempAction->isChecked() || mOverAction == tempAction)
    return;
  mOverAction = tempAction;
  update();
  QWidget::mouseMoveEvent(event);
}

void SideBarContainer::leaveEvent(QEvent *event) {
  mOverAction = nullptr;
  update();
  QWidget::leaveEvent(event);
}

QAction *SideBarContainer::actionAt(const QPoint &at) {
  int cont_margin = container_margin / 2;
  for (auto action : mActions) {

    QRect actionRect = rect();
    if(m_cOrientation == Vertical)
        actionRect = QRect(0, cont_margin, rect().width(), action_height);
    else
        actionRect = QRect(cont_margin, 0, action_width, rect().height());
    if (actionRect.contains(at))
      return action;

    if(m_cOrientation == Vertical)
        cont_margin += actionRect.height() + container_margin/3;
    else
        cont_margin += actionRect.width() + container_margin/3;
  }
  return nullptr;
}
