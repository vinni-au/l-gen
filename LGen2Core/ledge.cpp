/* Begin of file: ledge.cpp */

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

#include "ledge.hpp"

quint64 LEdge::m_lastid = 0;

LEdge::LEdge(QString name, LNode *node, LNode *source, QObject *parent) :
    QObject(parent), m_name(name), m_node(node), m_source(source)
{
    static quint64 id = 0;
    m_id = id++;
}

LEdge::LEdge(quint64 id, QString name, LNode *node, LNode *source, QObject *parent) :
    QObject(parent), m_name(name), m_node(node), m_source(source), m_id(id)
{
    if (id >= m_lastid)
        m_lastid = id + 1;
}

/* End of file: ledge.cpp */
