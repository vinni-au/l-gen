/* Begin of file: lnode.hpp */

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

#ifndef LNODE_HPP
#define LNODE_HPP

#include <QObject>
#include <QList>
#include <QString>
#include "ledge.hpp"

class LOntology;

//! Вершина сем.сети (внутреннее представление)
class LNode : public QObject
{
    Q_OBJECT

public:
    LNode(QString iri, QList<LEdge*> edges = QList<LEdge*>(), QObject *parent = 0);
    LNode(quint64 id, QString iri, QList<LEdge*> edges = QList<LEdge*>(), QObject *parent = 0);

    //! Добавляет дугу
    void addEgde(LEdge* edge);

    //! Возвращает IRI понятия, представленное вершиной
    /*!
      \sa m_iri
    */
    QString iri() const
    {   return m_iri;   }

    // TODO: check new IRI
    bool setIri(QString iri)
    {   m_iri = iri; return true;   }

    //! Возвращает список дуг, выходящих из вершины
    /*!
      \sa edgesCount()
    */
    QList<LEdge*> edges() const
    {   return m_edges; }

    //! Возвращает количество дуг, выходящих из вершины
    /*!
      \sa edges()
    */
    int edgesCount() const
    {   return m_edges.count(); }

    //! Возвращает указатель на онтологию, в которой находится понятие, представленное вершиной
    /*!
      \sa m_ontology, setOntology()
    */
    LOntology* ontology() const
    {   return m_ontology;  }

    //! Задаёт онтологию, в которой находится понятие, представленное вершиной
    /*!
      \param ontology указатель на онтологию
      \sa m_ontology, ontology()
    */
    void setOntology(LOntology* ontology)
    {   m_ontology = ontology;  }

    //! Определяет, является ли вершина листовой
    bool isLeaf() const;

    quint64 id() const
    {   return m_id;    }

signals:

public slots:

private:
    //! IRI понятия, представляемого вершиной
    /*!
      \sa iri()
    */
    QString m_iri;

    //! Список дуг, выходящих из вершины
    /*!
      \sa edges(), edgesCount()
    */
    QList<LEdge*> m_edges;

    //! Онтология, в которой находится понятие, представленное вершиной
    /*!
      \sa ontology(), setOntology()
    */
    LOntology* m_ontology;

    quint64 m_id;

    static quint64 m_lastid;
};

#endif // LNODE_HPP
/* End of file: lnode.hpp */
