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

#ifndef LONTOLOGYMODEL_HPP
#define LONTOLOGYMODEL_HPP

#include <QAbstractItemModel>
#include <QHash>
#include "LGen2Core/lontology.hpp"
#include "lontologymodeltreenode.hpp"

//! Модель для представления онтологии в виде дерева
class LOntologyModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit LOntologyModel(QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;

    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    LOntology* ontology() const
    {   return m_ontology;  }
    void setOntology(LOntology* ontology);

    void setCheckedOnlyLeaves(bool value)
    {   m_checkOnlyLeaves = value;    }

    void setItemsCheckable(bool checkable)
    {   m_itemsCheckable = checkable;   }

    QList<LNode*> checkedNodes() const
    {   return m_checkedNodes;  }

    virtual void onNodeChecked(LOntologyModelTreeNode* treeNode);
    virtual void onNodeUnchecked(LOntologyModelTreeNode* treeNode);

    LNode* nodeFromIndex(const QModelIndex& index) const
    {   return treenodeFromIndex(index)->node();    }

    QModelIndex indexFromIri(QString iri);
    QModelIndex indexFromId(quint64 id);

    void insertNodeOn(QModelIndex index, QString name);
    void deleteNode(quint64 id);

    void insertEdge(quint64 sid, quint64 did, QString title);

signals:
    void nodeChecked(LNode* node);
    void nodeUnchecked(LNode* node);

    void nodeAdded(LNode* node);
    void edgeAdded(LEdge* edge);

    void nodeDeleted(quint64 id);
    void edgeDeleted(quint64 id);

    void nodeChanged(LNode* node);

private:
    QHash<QString, QModelIndex> m_indexHash;
    LOntology* m_ontology;
    LOntologyModelTreeNode* m_rootNode;
    bool m_checkOnlyLeaves;
    QList<LNode*> m_checkedNodes;
    bool m_itemsCheckable;
    QString m_ancestor;

    LOntologyModelTreeNode* treenodeFromIndex(const QModelIndex& index) const;
};

#endif // LONTOLOGYMODEL_HPP
