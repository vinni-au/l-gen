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

    LNode* node = new LNode(iri, QList<LEdge*>(), this);
    m_nodes << node;
    m_nodesHash.insert(iri, node);
    m_nodesIdHash.insert(node->id(), node);
    emit nodeAdded(node);
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
    emit nodeAdded(node);
    return true;
}

bool LOntology::addNode(LNode *node, LNode *parent)
{
    if (addNode(node)) {
        addEdge("is-a", node, parent, true);
        addEdge("has-subclass", parent, node, true);
        return true;
    } else return false;
}

LEdge *LOntology::addEdge(QString name, QString sourceIri, QString destIri)
{
    LNode* source = m_nodesHash.value(sourceIri, 0);
    LNode* dest = m_nodesHash.value(destIri, 0);
    return addEdge(name, source, dest, false);
}

LEdge *LOntology::addEdge(QString name, LNode *source, LNode *dest, bool isa = false)
{
    //TODO: check whether edge can be added
    if (source && dest) {
        QString reverseName;
        LEdge* edge = new LEdge(name, dest, source);
        if (name == "is-a")
            reverseName = "has-subclass";
        else reverseName = name + "_reverse";
        if (!isa) {
            LEdge* egde = new LEdge(reverseName, source, dest);
            source->addEgde(edge);
            dest->addEgde(egde);
        }
        m_edges << edge;
        m_edgesHash.insert(edge->name(), edge);
        m_edgesIdHash.insert(edge->id(), edge);
        if (edge->name() != "has-subclass" && !edge->name().contains("_reverse"))
            emit edgeAdded(edge);
        return edge;
    } else return 0;
}

bool LOntology::hasParent(LNode *node, QString parentIRI)
{
    LEdge* edge = node->edgeFromName("is-a");
    LNode* parent;
    if (edge)
        parent = edge->node();
    else parent = 0;
    while (parent) {
        if (parent->iri() == parentIRI)
            return true;
        edge = parent->edgeFromName("is-a");
        if (edge)
            parent = edge->node();
        else parent = 0;
    }
    return false;
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
    if (doc.documentElement().tagName() == "lontology") {
        for (int i = 0; i < m_nodes.count(); ++i)
            delete m_nodes.at(i);
        for (int i = 0; i < m_edges.count(); ++i)
            delete m_edges.at(i);
        m_nodes.clear();
        m_edges.clear();

        QDomElement nodesElement = doc.documentElement().firstChildElement("nodes");
        if (!nodesElement.isNull()) {
            for (int i = 0; i < nodesElement.childNodes().count(); ++i) {
                QDomElement nodeElement = nodesElement.childNodes().at(i).toElement();
                quint64 id = nodeElement.attribute("id").toULongLong();
                QString iri = nodeElement.attribute("iri");
                LNode* node = new LNode(id, iri, QList<LEdge*>(), this);
                addNode(node);
                if (iri == "Thing")
                    m_root = node;
            }
        } else return false;

        QDomElement edgesElement = doc.documentElement().firstChildElement("edges");
        if (!edgesElement.isNull()) {
            for (int i = 0; i < edgesElement.childNodes().count(); ++i) {
                QDomElement edgeElement = edgesElement.childNodes().at(i).toElement();
                quint64 id = edgeElement.attribute("id").toULongLong();
                quint64 sid = edgeElement.attribute("sid").toULongLong();
                quint64 did = edgeElement.attribute("did").toULongLong();
                QString name = edgeElement.attribute("name");
                LNode* source = m_nodesIdHash.value(sid, 0);
                LNode* dest = m_nodesIdHash.value(did, 0);
                if (source && dest) {
                    LEdge* edge = addEdge(name, source, dest, true);
                    edge->setId(id);
                    source->addEgde(edge);
                }
            }
        } else return false;

        return true;
    } else return false;
}
