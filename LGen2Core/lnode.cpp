/* Begin of file: lnode.cpp */

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

#include "lnode.hpp"

quint64 LNode::m_lastid = 0;

LNode::LNode(QString iri, QList<LEdge *> edges, QObject *parent) :
    QObject(parent), m_iri(iri), m_edges(edges), m_ontology(0)
{    
    m_id = m_lastid++;
}

LNode::LNode(quint64 id, QString iri, QList<LEdge *> edges, QObject *parent) :
    QObject(parent), m_iri(iri), m_edges(edges), m_ontology(0), m_id(id)
{
    if (id >= m_lastid)
        m_lastid = id + 1;
}

void LNode::addEgde(LEdge *edge)
{
    m_edges << edge;
}

bool LNode::isLeaf() const
{
    int count = 0;
    for (int i = 0; i < m_edges.count(); ++i)
        if (m_edges.at(i)->name() == "has-subclass")
            ++count;
    return count == 0;
}
/* End of file: lnode.cpp */
