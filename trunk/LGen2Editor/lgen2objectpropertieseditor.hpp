/* Begin of file lgen2objectpropertieseditor.hpp */

/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef LGEN2OBJECTPROPERTIESEDITOR_HPP
#define LGEN2OBJECTPROPERTIESEDITOR_HPP

#include <QTreeView>

class LGen2ObjectPropertiesEditor : public QTreeView
{
    Q_OBJECT
public:
    explicit LGen2ObjectPropertiesEditor(QWidget *parent = 0);

signals:

public slots:

};

#endif // LGEN2OBJECTPROPERTIESEDITOR_HPP

/* End of file lgen2objectpropertieseditor.hpp */
