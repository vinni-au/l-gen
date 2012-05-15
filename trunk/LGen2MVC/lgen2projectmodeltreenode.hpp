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

#ifndef LGEN2PROJECTMODELTREENODE_HPP
#define LGEN2PROJECTMODELTREENODE_HPP

#include <QObject>
#include <QVariant>
#include "LGen2Core/lgen2project.hpp"

class LGen2ProjectModelTreeNode : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Root = 0,
        ProjectName,
        Path,
        Text
    };

    explicit LGen2ProjectModelTreeNode(LGen2Project* project,
                QString text = QString(), Type type = Text, QObject *parent = 0);

    LGen2Project* project() const
    {   return m_project;   }

    QString text() const
    {   return m_text;  }

    LGen2ProjectModelTreeNode* parent() const
    {   return m_parent;    }
    void setParent(LGen2ProjectModelTreeNode* node)
    {   m_parent = node;    }

    QList<LGen2ProjectModelTreeNode*> children() const
    {   return m_children;  }
    void addChild(LGen2ProjectModelTreeNode* node)
    {   m_children << node; }

    LGen2ProjectModelTreeNode* childAt(int i)
    {
        if (i < m_children.count() || i >= 0)
            return m_children.at(i);
        return 0;
    }

    QVariant data(int role = Qt::DisplayRole);

    int childCount() const
    {   return m_children.count();  }

private:
    LGen2Project* m_project;
    QString m_text;

    Type m_type;

    LGen2ProjectModelTreeNode* m_parent;
    QList<LGen2ProjectModelTreeNode*> m_children;

};

typedef LGen2ProjectModelTreeNode PMTreeNode;

#endif // LGEN2PROJECTMODELTREENODE_HPP
