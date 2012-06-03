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
            if (!m_edges.contains(cur))
                m_edges << cur;
            if (!m_edgesHash.contains(cur->name(), cur))
                m_edgesHash.insert(cur->name(), cur);
        }
    }
}

LOntology::~LOntology()
{
    for (int i = 0; i < m_nodes.count(); ++i)
        delete m_nodes.at(i);
    for (int i = 0; i < m_edges.count(); ++i)
        delete m_edges.at(i);
}

bool LOntology::addNode(QString iri)
{
    if (m_nodesHash.contains(iri))
        return false;

    LNode* node = new LNode(iri);
    m_nodes << node;
    m_nodesHash.insert(iri, node);
    return true;
}

bool LOntology::addNode(LNode *node)
{
    if (m_nodes.contains(node))
        return false;
    if (m_nodesHash.contains(node->iri()))
        return false;
    if (m_nodesIdHash.contains(node->id()))
        return false;

    m_nodes << node;
    m_nodesHash.insert(node->iri(), node);
    m_nodesIdHash.insert(node->id(), node);
    return true;
}

LEdge *LOntology::addEdge(QString name, QString sourceIri, QString destIri)
{
    LNode* source = m_nodesHash.value(sourceIri, 0);
    LNode* dest = m_nodesHash.value(destIri, 0);
    return addEdge(name, source, dest);
}

LEdge *LOntology::addEdge(QString name, LNode *source, LNode *dest)
{
    if (source && dest) {
        LEdge* edge = new LEdge(name, dest, source);
        m_edges << edge;
        m_edgesHash.insert(edge->name(), edge);
        m_edgesIdHash.insert(edge->id(), edge);
        return edge;
    } else return 0;
}

QDomDocument LOntology::toXML()
{
    QDomDocument doc = QXML"lontology";
    QDomDocument nodes = QXML"nodes";
    QDomDocument edges = QXML"edges";

    for (int i = 0; i < m_nodes.count(); ++i) {
        LNode* node = m_nodes.at(i);
        nodes << (QXML"node"
                      < "@id" > node->id()
                      < "@iri" > node->iri()
                  );
    }

    for (int i = 0; i < m_edges.count(); ++i) {
        LEdge* edge = m_edges.at(i);
        edges << (QXML"edge"
                      < "@id" > edge->id()
                      < "@sid" > edge->source()->id()
                      < "@did" > edge->node()->id()
                      < "@name" > edge->name()
                     );
    }

    doc << nodes;
    doc << edges;

    return doc;
}

bool LOntology::fromXML(const QDomDocument &doc)
{
    if (doc.toElement().tagName() == "lontology") {
        for (int i = 0; i < m_nodes.count(); ++i)
            delete m_nodes.at(i);
        for (int i = 0; i < m_edges.count(); ++i)
            delete m_edges.at(i);
        m_nodes.clear();
        m_edges.clear();

        QDomElement nodesElement = doc.firstChildElement("nodes");
        if (!nodesElement.isNull()) {
            for (int i = 0; i < nodesElement.childNodes().count(); ++i) {
                QDomElement nodeElement = nodesElement.childNodes().at(i).toElement();
                quint64 id = nodeElement.attribute("id").toULongLong();
                QString iri = nodeElement.attribute("iri");
                LNode* node = new LNode(id, iri);
                addNode(node);
            }
        } else return false;

        QDomElement edgesElement = doc.firstChildElement("edges");
        if (!edgesElement.isNull()) {
            for (int i = 0; i < edgesElement.childNodes().count(); ++i) {
                QDomElement edgeElement = edgesElement.childNodes().at(i).toElement();
                quint64 id = edgeElement.attribute("id").toULongLong();
                quint64 sid = edgeElement.attribute("sid").toULongLong();
                quint64 did = edgeElement.attribute("did").toULongLong();
                QString name = edgeElement.attribute("name");
                LNode* source = m_nodesIdHash.value(sid, 0);
                LNode* dest = m_nodesIdHash.value(did, 0);
                if (source && dest)
                    addEdge(name, source, dest)->setId(id);
            }
        } else return false;

        return true;
    } else return false;
}
