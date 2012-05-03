/* Begin of file: lontology.cpp */

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

#include "lontology.hpp"

LOntology::LOntology(LNode *root, QList<LNode *> nodes, QObject *parent) :
    QObject(parent), m_root(root), m_nodes(nodes)
{
    int count = nodes.count();
    for (int i = 0; i < count; ++i) {
        LNode* current = nodes.at(i);
        current->setOntology(this);
        m_nodesHash[current->iri()] = current;
        for (int j = 0; j < current->edgesCount(); ++j) {
            LEdge* cur = current->edges().at(j);
            if (!m_edgesHash.contains(cur->name(), cur))
                m_edgesHash.insert(cur->name(), cur);
        }
    }
}

/* End of file: lontology.cpp */
