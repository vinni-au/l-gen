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

#include "lontologymodel.hpp"

LOntologyModel::LOntologyModel(QObject *parent) :
    QAbstractItemModel(parent), m_ontology(0), m_rootNode(0),
    m_checkOnlyLeaves(true), m_checkedNodes(QList<LNode*>()), m_itemsCheckable(false)
{   }

QModelIndex LOntologyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_rootNode || row < 0 || column < 0 || column > 0)
        return QModelIndex();
    LOntologyModelTreeNode* parentNode = nodeFromIndex(parent);
    LOntologyModelTreeNode* childNode = parentNode->children().at(row);
    if (!childNode)
        return QModelIndex();
    QModelIndex result = createIndex(row, 0, childNode);
    const_cast<QHash<QString, QModelIndex>* >(&m_indexHash)->insert(childNode->node()->iri(), result);
    return result;
}

QModelIndex LOntologyModel::parent(const QModelIndex &child) const
{
    LOntologyModelTreeNode* node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();
    LOntologyModelTreeNode* parentNode = node->parent();
    if (!parentNode)
        return QModelIndex();
    LOntologyModelTreeNode* grandParentNode = parentNode->parent();
    if (!grandParentNode)
        return QModelIndex();
    int row = grandParentNode->children().indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

int LOntologyModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    LOntologyModelTreeNode* node = nodeFromIndex(parent);
    if (!node)
        return 0;
    return node->childCount();
}

int LOntologyModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant LOntologyModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::CheckStateRole && role != Qt::EditRole)
        return QVariant();

    LOntologyModelTreeNode* node = nodeFromIndex(index);
    if (!node)
        return QVariant();

    if (index.column() == 0) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return node->node()->iri();
        if (role == Qt::CheckStateRole) {
            if (!m_itemsCheckable)
                return QVariant();
            if (m_checkOnlyLeaves) {
                if (node->childCount())
                    return QVariant();
                return node->checked();
            } else return node->checked();
        }
    }
    return QVariant();
}

bool LOntologyModel::setData(const QModelIndex &index, const QVariant& data, int role)
{
    if (role != Qt::CheckStateRole && role != Qt::EditRole)
        return false;
    LOntologyModelTreeNode* node = nodeFromIndex(index);
    if (!node)
        return false;
    if (index.column() == 0) {
        if (role == Qt::CheckStateRole) {
            node->setChecked(!node->checked());
            if (node->checked()) {
                emit nodeChecked(node->node());
                onNodeChecked(node);
            } else {
                emit nodeUnchecked(node->node());
                onNodeUnchecked(node);
            }
            emit dataChanged(index, index);
            return true;
        } else if (role == Qt::EditRole) {
            if (node->node()->setIri(data.toString())) {
                emit dataChanged(index, index);
                return true;
            } else return false;
        }
    }
    return false;
}

Qt::ItemFlags LOntologyModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    return QAbstractItemModel::flags(index);
}

LOntologyModelTreeNode* LOntologyModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid())
        return static_cast<LOntologyModelTreeNode*>(index.internalPointer());
    return m_rootNode;
}

void LOntologyModel::onNodeChecked(LOntologyModelTreeNode *treeNode)
{
    m_checkedNodes << treeNode->node();
}

void LOntologyModel::onNodeUnchecked(LOntologyModelTreeNode *treeNode)
{
    m_checkedNodes.removeAll(treeNode->node());
}

QModelIndex LOntologyModel::indexFromIri(QString iri)
{
    return m_indexHash.value(iri, QModelIndex());
}

void LOntologyModel::insertNodeOn(QModelIndex index, QString name)
{
    LOntologyModelTreeNode* treeNode = nodeFromIndex(index);
    if (treeNode) {
        LNode* node = new LNode(name);
        LOntologyModelTreeNode* newNode = new LOntologyModelTreeNode(node);
        newNode->setParent(treeNode);
        treeNode->addChild(newNode);
        m_ontology->addNode(node, treeNode->node());
        //FIXME: not reset!
        reset();
    }
}

void LOntologyModel::setOntology(LOntology *ontology)
{
    m_ontology = ontology;
    QList<LNode*> done;
    QList<LNode*> toProcess;
    QMap<LNode*, LOntologyModelTreeNode*> nodes;
    LNode* root = ontology->root();
    toProcess << root;
    m_rootNode = new LOntologyModelTreeNode(root, LOntologyModelTreeNode::Root);
    nodes[root] = m_rootNode;
    done << root;
    while (!toProcess.empty()) {
        LNode* current = toProcess.at(0);
        for (int i = 0; i < current->edgesCount(); ++i) {
            QString link = current->edges().at(i)->name();
            if (link == "has-subclass") {
                LNode* curChild = current->edges().at(i)->node();
                LOntologyModelTreeNode* curChildNode = new LOntologyModelTreeNode(curChild);
                curChildNode->setParent(nodes[current]);
                nodes[current]->addChild(curChildNode);
                nodes[curChild] = curChildNode;
                toProcess << curChild;
            }
        }
        toProcess.removeAll(current);
    }
    reset();

    QObject::connect(ontology, SIGNAL(nodeAdded(LNode*)),
                     SIGNAL(nodeAdded(LNode*)));
    QObject::connect(ontology, SIGNAL(edgeAdded(LEdge*)),
                     SIGNAL(edgeAdded(LEdge*)));
}
