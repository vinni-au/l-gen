/* Begin of file: lontology.cpp */
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
