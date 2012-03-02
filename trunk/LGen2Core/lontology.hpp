/* Begin of file: lontology.hpp */
#ifndef LONTOLOGY_HPP
#define LONTOLOGY_HPP

#include <QObject>
#include <QList>
#include <QHash>
#include <QMultiHash>
#include "lnode.hpp"

class LOntology : public QObject
{
    Q_OBJECT

    LNode* m_root;
    QList<LNode*> m_nodes;
    QHash<QString, LNode*> m_nodesHash;
    QMultiHash<QString, LEdge*> m_edgesHash;

public:
    explicit LOntology(LNode* root, QList<LNode*> nodes, QObject *parent = 0);

    LNode* root() const
    {   return m_root;  }

    QList<LNode*> nodes() const
    {   return m_nodes; }

    LNode* nodeFromIri(QString iri)
    {   return m_nodesHash.value(iri, 0);   }

    QList<LEdge*> edgesFromName(QString name)
    {   return m_edgesHash.values(name);    }

signals:

public slots:

};

#endif // LONTOLOGY_HPP
/* End of file: lontology.hpp */
