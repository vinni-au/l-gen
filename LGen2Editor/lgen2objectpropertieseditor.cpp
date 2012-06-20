/* Begin of file lgen2objectpropertieseditor.cpp */

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

#include "lgen2objectpropertieseditor.hpp"
#include "LGen2MVC/lontologymodel.hpp"

LGen2ObjectPropertiesEditor::LGen2ObjectPropertiesEditor(QWidget *parent) :
    QTreeView(parent)
{
}

void LGen2ObjectPropertiesEditor::onCurrentChanged(QModelIndex current, QModelIndex)
{
    LOntologyModel* m = static_cast<LOntologyModel*>(model());
    if (m) {
        LNode* node = m->nodeFromIndex(current);
        if (node)
            emit nodeSelected(node->id());
    }
}

void LGen2ObjectPropertiesEditor::setModel(QAbstractItemModel *m)
{
    QTreeView::setModel(m);
    expandAll();
    collapseAll();
    if (!selectionModel())
        setSelectionModel(new QItemSelectionModel(model()));
    QObject::connect(selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                     SLOT(onCurrentChanged(QModelIndex,QModelIndex)));
}

void LGen2ObjectPropertiesEditor::selectNode(quint64 id)
{
//FIXME: expand if needed
    LOntologyModel* m = static_cast<LOntologyModel*>(model());
    if (m)
        setCurrentIndex(m->indexFromId(id));
}

void LGen2ObjectPropertiesEditor::deleteNode(quint64 id)
{
    LOntologyModel* m = static_cast<LOntologyModel*>(model());
    if (m)
        m->deleteNode(id);
}

void LGen2ObjectPropertiesEditor::focusInEvent(QFocusEvent *)
{
    emit currentChanged(currentIndex(), currentIndex());
}

/* End of file lgen2objectpropertieseditor.hpp */
