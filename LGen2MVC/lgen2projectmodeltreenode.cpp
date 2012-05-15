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

#include "lgen2projectmodeltreenode.hpp"
#include <QDir>

LGen2ProjectModelTreeNode::LGen2ProjectModelTreeNode(LGen2Project *project,
            QString text, Type type, QObject *parent) :
    QObject(parent), m_project(project), m_text(text), m_type(type),
    m_parent(0)
{   }

QVariant LGen2ProjectModelTreeNode::data(int role)
{
    if (role == Qt::DisplayRole) {
        switch (m_type) {
            case Root:
                return QVariant();
            case ProjectName:
                return QVariant(m_project->name());
            case Text:
                return QVariant(m_text);
            case Path: {
                QStringList strs = m_text.split(QDir::separator());
                if (!strs.isEmpty())
                    return QVariant(strs.last());
                else return QVariant(m_text);
            }
            default:
                return QVariant();
        }
    } else if (role == Qt::ToolTipRole) {
        switch (m_type) {
        case Path:
            return QVariant(m_text);
        case ProjectName:
            return QVariant(m_project->filename());
        default:
            return QVariant();
        }
    }
    return QVariant();
}
