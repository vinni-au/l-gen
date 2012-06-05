/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This file is a part of L-Gen 2.0
 *
 * L-Gen 2.0 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * L-Gen 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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

