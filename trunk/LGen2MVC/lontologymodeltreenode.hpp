/* Begin of file: lontologymodeltreenode.hpp */

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

#ifndef LONTOLOGYMODELTREENODE_HPP
#define LONTOLOGYMODELTREENODE_HPP

#include <QObject>
#include <QList>
#include <LGen2Core/lnode.hpp>

//! Вершина дерева для модели представления онтологии
class LOntologyModelTreeNode : public QObject
{
    Q_OBJECT
public:
    //! Тип вершины
    enum Type
    {
        Root = 0,   /*!< Корневая вершина */
        Common      /*!< Обычная вершина */
    };

    LOntologyModelTreeNode(LNode* node, Type type = Common, QObject *parent = 0);

    LNode* node() const
    {   return m_node;  }

    LOntologyModelTreeNode* parent() const
    {   return m_parent;    }
    void setParent(LOntologyModelTreeNode* node)
    {   m_parent = node;    }

    QList<LOntologyModelTreeNode*> children() const
    {   return m_children;  }
    void addChild(LOntologyModelTreeNode* node)
    {   m_children << node; }

    int childCount() const
    {   return m_children.count();  }

    bool checked() const;
    void setChecked(bool checked)
    {   m_checked = checked;    }

private:
    LNode* m_node;
    LOntologyModelTreeNode* m_parent;
    QList<LOntologyModelTreeNode*> m_children;
    bool m_checked;
};

typedef LOntologyModelTreeNode OMTreeNode;

#endif // LONTOLOGYMODELTREENODE_HPP
/* Begin of file: lontologymodeltreenode.hpp */
