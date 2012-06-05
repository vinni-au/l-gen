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

#ifndef TREEBOX_HPP
#define TREEBOX_HPP

#include <QComboBox>
#include <QDirModel>
#include <QTreeView>
#include <QEvent>
#include <QMouseEvent>
#include <QModelIndex>

class TreeBox : public QComboBox
{
    Q_OBJECT
public:
    TreeBox(QWidget* parent = 0);

    bool eventFilter(QObject* object, QEvent* event);

    virtual void showPopup();

    virtual void hidePopup();

private:
    bool skipNextHide;
};

#endif // TREEBOX_HPP
