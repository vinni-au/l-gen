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

#ifndef LGEN2PROJECTMODEL_HPP
#define LGEN2PROJECTMODEL_HPP

#include <QAbstractItemModel>
#include "LGen2Core/lgen2project.hpp"
#include "lgen2projectmodeltreenode.hpp"

class LGen2ProjectModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit LGen2ProjectModel(QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &) const;

    virtual QVariant data(const QModelIndex &index, int role) const;

    LGen2Project* project() const
    {   return m_project;   }
    void setProject(LGen2Project* project);

    void clear();

protected:

private:
    LGen2Project* m_project;

    LGen2ProjectModelTreeNode* m_rootNode;

    LGen2ProjectModelTreeNode* nodeFromIndex(const QModelIndex& index) const;

};

#endif // LGEN2PROJECTMODEL_HPP
