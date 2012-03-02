/* Begin of file: lnode.hpp */
#ifndef LNODE_HPP
#define LNODE_HPP

#include <QObject>
#include <QList>
#include <QString>
#include "ledge.hpp"

class LOntology;

class LNode : public QObject
{
    Q_OBJECT

    QString m_iri;
    QList<LEdge*> m_edges;
    LOntology* m_ontology;

public:
    LNode(QString iri, QList<LEdge*> edges = QList<LEdge*>(), QObject *parent = 0);

    void addEgde(LEdge* edge);

    QString iri() const
    {   return m_iri;   }

    QList<LEdge*> edges() const
    {   return m_edges; }
    int edgesCount() const
    {   return m_edges.count(); }

    LOntology* ontology() const
    {   return m_ontology;  }
    void setOntology(LOntology* ontology)
    {   m_ontology = ontology;  }

    bool isLeaf() const;

signals:

public slots:

};

#endif // LNODE_HPP
/* End of file: lnode.hpp */
