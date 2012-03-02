/* Begin of file: lnode.cpp */
#include "lnode.hpp"

LNode::LNode(QString iri, QList<LEdge *> edges, QObject *parent) :
    QObject(parent), m_iri(iri), m_edges(edges), m_ontology(0)
{   }

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
