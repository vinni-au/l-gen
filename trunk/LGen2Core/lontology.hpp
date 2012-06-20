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

#ifndef LONTOLOGY_HPP
#define LONTOLOGY_HPP

#include <QObject>
#include <QList>
#include <QHash>
#include <QMultiHash>
#include "lnode.hpp"
#include "3rdparty/QSugar/QSugar.hpp"

//! Онтология
class LOntology : public QObject
{
    Q_OBJECT
public:
    explicit LOntology(LNode* root, QList<LNode*> nodes, QObject *parent = 0);
    ~LOntology();

    //! Возвращает указатель на корневую вершину
    /*!
      \sa m_root
    */
    LNode* root() const
    {   return m_root;  }

    //! Возвращает список всех вершин
    /*!
      \sa m_nodes
    */
    QList<LNode*> nodes() const
    {   return m_nodes; }

    QList<LEdge*> edges() const
    {   return m_edges; }

    //! Возвращает указатель на вершину по IRI
    /*!
      \param iri IRI искомой вершины
      \sa m_nodesHash
    */
    LNode* nodeFromIri(QString iri)
    {   return m_nodesHash.value(iri, 0);   }

    //! Возвращает указатель на вершину по id
    LNode* nodeFromId(quint64 id)
    {   return m_nodesIdHash.value(id, 0);  }

    //! Возвращает список дуг, выходящих из вершины с определённым IRI
    /*!
      \param iri IRI вершины
      \sa m_edgesHash
    */
    QList<LEdge*> edgesFromNode(QString iri)
    {   return m_edgesHash.values(iri);    }

    bool addNode(QString iri);
    bool addNode(LNode* node);
    bool addNode(LNode *node, LNode* parent);

    LEdge* addEdge(QString name, QString sourceIri, QString destIri);
    LEdge* addEdge(QString name, LNode* source, LNode* dest);

    QDomDocument toXML();
    bool fromXML(const QDomDocument& doc);

    bool hasParent(LNode* node, QString parentIRI);

signals:
    void nodeAdded(LNode* node);
    void edgeAdded(LEdge* edge);

private:
    //! Указатель на вершину, представляющую корневое понятие (Thing)
    /*!
      \sa root()
    */
    LNode* m_root;

    //! Список вершин
    /*!
      \sa nodes()
    */
    QList<LNode*> m_nodes;

    //! Список дуг
    QList<LEdge*> m_edges;

    //! Хэш-таблица вершин (ключ - IRI)
    /*!
      \sa nodeFromIri()
    */
    QHash<QString, LNode*> m_nodesHash;

    //! Мультихэш дуг, выходящих из вершин (ключ - IRI)
    /*!
      \sa edgesFromNode()
    */
    QMultiHash<QString, LEdge*> m_edgesHash;

    QHash<quint64, LNode*> m_nodesIdHash;
    QHash<quint64, LEdge*> m_edgesIdHash;
};

#endif // LONTOLOGY_HPP
