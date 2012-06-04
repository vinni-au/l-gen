#include "treebox.hpp"

TreeBox::TreeBox(QWidget *parent) :
    QComboBox(parent), skipNextHide(false)
{
    setView(new QTreeView(this));
    static_cast<QTreeView*>(view())->setHeaderHidden(true);
    view()->viewport()->installEventFilter(this);
}

bool TreeBox::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress && object == view()->viewport()) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QModelIndex index = view()->indexAt(mouseEvent->pos());
        if (!view()->visualRect(index).contains(mouseEvent->pos()))
            skipNextHide = true;
    }
    return false;
}

void TreeBox::showPopup()
{
    setRootModelIndex(QModelIndex());
    QComboBox::showPopup();
}

void TreeBox::hidePopup()
{
    setRootModelIndex(view()->currentIndex().parent());
    setCurrentIndex(view()->currentIndex().row());
    if (skipNextHide)
        skipNextHide = false;
    else QComboBox::hidePopup();
}

