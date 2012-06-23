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

#include <QContextMenuEvent>
#include "lgen2objectpropertieseditor.hpp"
#include "LGen2MVC/lontologymodel.hpp"

LGen2ObjectPropertiesEditor::LGen2ObjectPropertiesEditor(QWidget *parent) :
    QTreeView(parent), m_contextNode(0)
{
    m_contextMenu = new QMenu;
    QMenu* addMenu = m_contextMenu->addMenu("Добавить");
    QAction* actSibling = addMenu->addAction("Вершину",
                                             this, SLOT(on_actSibling()));
    QAction* actChild = addMenu->addAction("Потомок",
                                           this, SLOT(on_actChild()));
    QAction* actRename = m_contextMenu->addAction("Переименовать",
                                                  this, SLOT(on_actRename()));
    QAction* actDelete = m_contextMenu->addAction("Удалить",
                                                  this, SLOT(on_actDelete()));
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

void LGen2ObjectPropertiesEditor::contextMenuEvent(QContextMenuEvent *e)
{
    QModelIndex index = indexAt(e->pos());
    LOntologyModel* m = static_cast<LOntologyModel*>(model());
    if (m) {
        LNode* node = m->nodeFromIndex(index);
        if (node) {
            m_contextIndex = index;
            m_contextNode = node;
            m_contextMenu->exec(e->globalPos());
        }
    }
}

void LGen2ObjectPropertiesEditor::on_actChild()
{
    if (m_contextNode)
        emit addNodeRequest(m_contextNode->iri());
}

void LGen2ObjectPropertiesEditor::on_actDelete()
{
    if (m_contextNode)
        emit deleteNodeRequest(m_contextNode->iri());
}

void LGen2ObjectPropertiesEditor::on_actRename()
{
    if (m_contextNode) {
        edit(m_contextIndex);
    }
}

void LGen2ObjectPropertiesEditor::on_actSibling()
{
    if (m_contextNode) {
        if (m_contextNode->iri().startsWith("#")) {
            emit addNodeRequest(m_contextNode->iri());
            return;
        }
        LEdge* edge = m_contextNode->edgeFromName("is-a");
        if (edge)
            emit addNodeRequest(edge->node()->iri());
    }
}

void LGen2ObjectPropertiesEditor::focusInEvent(QFocusEvent *)
{
    emit currentChanged(currentIndex(), currentIndex());
}
