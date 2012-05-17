/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This file is a part of L-Gen 2.0
 *
 * L-Gen 2.0 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * L-Gen 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "lgen2projectmodel.hpp"

LGen2ProjectModel::LGen2ProjectModel(QObject *parent) :
    QAbstractItemModel(parent), m_project(0), m_rootNode(0)
{   }

QModelIndex LGen2ProjectModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_rootNode || row < 0 || column != 0)
        return QModelIndex();

    LGen2ProjectModelTreeNode* parentNode = nodeFromIndex(parent);
    LGen2ProjectModelTreeNode* childNode = parentNode->childAt(row);
    if (!childNode)
        return QModelIndex();
    return createIndex(row, 0, childNode);
}

QModelIndex LGen2ProjectModel::parent(const QModelIndex &child) const
{
    LGen2ProjectModelTreeNode* node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();
    LGen2ProjectModelTreeNode* parentNode = node->parent();
    if (!parentNode)
        return QModelIndex();
    LGen2ProjectModelTreeNode* grandParentNode = parentNode->parent();
    if (!grandParentNode)
        return QModelIndex();
    int row = grandParentNode->children().indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

int LGen2ProjectModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    LGen2ProjectModelTreeNode* node = nodeFromIndex(parent);
    if (!node)
        return 0;
    return node->childCount();
}

int LGen2ProjectModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant LGen2ProjectModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::ToolTipRole)
        return QVariant();

    LGen2ProjectModelTreeNode* node = nodeFromIndex(index);
    if (!node)
        return QVariant();

    if (index.column() == 0) {
        return node->data(role);
    }

    return QVariant();
}

LGen2ProjectModelTreeNode* LGen2ProjectModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid())
        return static_cast<LGen2ProjectModelTreeNode*>(index.internalPointer());
    return m_rootNode;
}

void LGen2ProjectModel::setProject(LGen2Project *project)
{
    clear();
    m_project = project;
    m_rootNode = new PMTreeNode(project, QString(),
                                               PMTreeNode::Root);

    PMTreeNode* nameNode = new PMTreeNode(project, QString(),
                                          PMTreeNode::ProjectName);
    nameNode->setParent(m_rootNode);
    m_rootNode->addChild(nameNode);

/*    PMTreeNode* pathNode = new PMTreeNode(project, project->filename(),
                                          PMTreeNode::Path);
    pathNode->setParent(nameNode);
    nameNode->addChild(pathNode);*/

    PMTreeNode* dNode = new PMTreeNode(project, "Онтологии предметной области",
                                       PMTreeNode::Text);
    dNode->setParent(nameNode);
    nameNode->addChild(dNode);

    PMTreeNode* d1Node = new PMTreeNode(project, project->dfilename(),
                                        PMTreeNode::Path);
    d1Node->setParent(dNode);
    dNode->addChild(d1Node);

    PMTreeNode* tNode = new PMTreeNode(project, "Онтологии шаблонов задач",
                                       PMTreeNode::Text);
    tNode->setParent(nameNode);
    nameNode->addChild(tNode);

    PMTreeNode* t1Node = new PMTreeNode(project, project->tfilename(),
                                        PMTreeNode::Path);
    t1Node->setParent(tNode);
    tNode->addChild(t1Node);

    PMTreeNode* pNode = new PMTreeNode(project, "Параметры генерации",
                                       PMTreeNode::Text);
    pNode->setParent(nameNode);
    nameNode->addChild(pNode);

    reset();
}

void LGen2ProjectModel::clear()
{
    // TODO: write a correct clean
    m_project = 0;
    m_rootNode = 0;
}
