/* Begin of file lgen2diagrameditor.cpp */

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

#include "lgen2diagrameditor.hpp"
#include <QContextMenuEvent>

LGen2DiagramEditor::LGen2DiagramEditor(QWidget *parent, QMenu *contextMenu):
    QGraphicsView(parent), m_contextMenu(contextMenu)
{
    m_scene = new DiagramScene;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setDragMode(QGraphicsView::RubberBandDrag);

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    setScene(m_scene);

    QObject::connect(m_scene, SIGNAL(selectionChanged()),
                     SLOT(onSceneSelectionChanged()));
}

void LGen2DiagramEditor::addNode(unsigned id, QString title)
{
    static QMenu* menu = new QMenu;
    static QAction* act = menu->addAction("Удалить вершину", this, SLOT(deleteSelectedNode()));
    DiagramItem* node = new DiagramItem(id, DiagramItem::TextRectangle, title, menu);
    node->setPos(mapToScene(QPoint(width() / 2, height() / 2)));
    m_items.insert(id, node);
    m_scene->addItem(node);
}

void LGen2DiagramEditor::changeNodeText(unsigned id, QString newtitle)
{
    DiagramItem* node = m_items[id];
    node->setText(newtitle);
    node->update();
}

void LGen2DiagramEditor::addArrow(Arrow *arrow)
{
    static QMenu* menu = new QMenu;
    static QAction* act = menu->addAction("Удалить связь", this, SLOT(deleteSelectedLink()));
    arrow->setContextMenu(menu);
    m_links << arrow;
}

void LGen2DiagramEditor::deleteNode(unsigned id)
{
    //setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    m_scene->blockSignals(true);
    DiagramItem* item = m_items[id];
    if (item) {
        QList<Arrow*> arrows = item->arrows();
        for (int i = 0; i < arrows.count(); ++i)
            m_links.removeAll(arrows[i]);
        item->removeArrows();
        m_items.remove(id);
        m_scene->removeItem(item);
        delete item;
    }
    m_scene->blockSignals(false);
    //setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //update();
}

void LGen2DiagramEditor::addLink(unsigned sid, unsigned did, QString title)
{
    DiagramItem* i1 = m_items[sid];
    DiagramItem* i2 = m_items[did];
    static QMenu* menu = new QMenu;
    static QAction* act = menu->addAction("Удалить связь", this, SLOT(deleteSelectedLink()));
    Arrow* a = new Arrow(i1, i2, title, 0, m_scene);
    a->setContextMenu(menu);
    m_links << a;
    i1->addArrow(a);
    i2->addArrow(a);
    //m_scene->addItem(a);
    if (title == "is-a")
        a->setColor(Qt::darkGreen);
    else if (title == "sub")
        a->setColor(Qt::darkYellow);
}

void LGen2DiagramEditor::deleteLink(unsigned sid, unsigned did)
{
    Arrow* a = 0;
    for (int i = 0; i < m_links.count(); ++i) {
        a = m_links[i];
        //FIXME: WTF??
        if (a && (unsigned long long)a->endItem() != 0xfeeefeee  && (unsigned long long)a->startItem() != 3722304989)
            if (a->startItem()->id() == sid &&
                    a->endItem()->id() == did) {
                a = m_links[i];
                break;
            }
    }
    m_links.removeAll(a);
    //m_scene->removeItem(a);

    Arrow* arrow = 0;
    DiagramItem* si = m_items[sid];
    for (int i = 0; i < si->arrows().count(); ++i) {
        arrow = si->arrows().at(i);
        if (arrow->endItem()->id() == did)
            break;
        arrow = 0;
    }
    if (arrow)
        si->removeArrow(arrow);

    DiagramItem* di = m_items[did];
    for (int i = 0; i < di->arrows().count(); ++i) {
        arrow = di->arrows().at(i);
        if (arrow->startItem()->id() == sid)
            break;
        arrow = 0;
    }
    if (arrow)
        di->removeArrow(arrow);

    m_scene->removeItem(arrow);
    //si->removeArrowTo(di);
    //di->removeArrowFrom(si);
}

void LGen2DiagramEditor::onSceneSelectionChanged()
{
    QList<QGraphicsItem*> items = m_scene->selectedItems();
    if (items.count() == 1) {
        DiagramItem* item = qgraphicsitem_cast<DiagramItem*>(items[0]);
        if (item) {
            if (item->diagramItemType() == DiagramItem::TextRectangle)
                emit nodeSelected(item->id());
        } else {
            Arrow* arrow = qgraphicsitem_cast<Arrow*>(items[0]);
            if (arrow)
                emit linkSelected(arrow->startItem()->id(), arrow->endItem()->id());
        }
    }
    if (!items.count())
        emit selectionCleared();
}

unsigned LGen2DiagramEditor::selectedFrameId()
{
    QList<QGraphicsItem*> items = m_scene->selectedItems();
    if (items.count() == 1) {
        DiagramItem* item = qgraphicsitem_cast<DiagramItem*>(items[0]);
        if (item)
            if (item->diagramItemType() == DiagramItem::TextRectangle)
                return item->id();
    }
    return -1;
}

void LGen2DiagramEditor::selectNode(unsigned id)
{
    blockSignals(true);
    QList<QGraphicsItem*> items = m_scene->items();
    foreach (QGraphicsItem* item, items) {
        DiagramItem *ditem = qgraphicsitem_cast<DiagramItem*>(item);
        if (ditem)
            if (ditem->id() == id)
                ditem->imitateMousePress();
    }
    blockSignals(false);
}

void LGen2DiagramEditor::deleteSelectedNode()
{
    unsigned id = selectedFrameId();
    if (id != -1)
        emit nodeDeleteRequest(id);
}

void LGen2DiagramEditor::deleteSelectedLink()
{
    QList<QGraphicsItem*> items = m_scene->selectedItems();
    if (items.count() == 1) {
        Arrow* a = qgraphicsitem_cast<Arrow*>(items[0]);
        if (a) {
            if (a->text() == "is-a") {
                emit isaDeleted(a->startItem()->id(), a->endItem()->id());
            } else if (a->text() == "sub") {
                emit apoDeleted(a->startItem()->id(), a->endItem()->id());
            }
            //deleteLink(a->startItem()->id(), a->endItem()->id());
        }
    }
}

//TODO: delete selected items
void LGen2DiagramEditor::deleteSelectedItems()
{

}

void LGen2DiagramEditor::zoomIn()
{
    scale(1.15, 1.15);
}

void LGen2DiagramEditor::zoonOut()
{
    scale(1 / 1.15, 1 / 1.15);
}

QDomElement LGen2DiagramEditor::toXML(QDomDocument &doc)
{
    QDomElement dElem = doc.createElement("diagram");

    foreach (QGraphicsItem* item, m_items) {
        DiagramItem* ditem = qgraphicsitem_cast<DiagramItem*>(item);
        if (ditem) {
            QDomElement ielem = doc.createElement("item");
            ielem.setAttribute("x", ditem->x());
            ielem.setAttribute("y", ditem->y());
            ielem.setAttribute("title", ditem->text());
            ielem.setAttribute("id", ditem->id());
            dElem.appendChild(ielem);
        }
    }

    foreach (Arrow* arrow, m_links) {
        QDomElement aelem = doc.createElement("link");
        aelem.setAttribute("text", arrow->text());
        aelem.setAttribute("sid", arrow->startItem()->id());
        aelem.setAttribute("did", arrow->endItem()->id());
        dElem.appendChild(aelem);
    }

    return dElem;
}

void LGen2DiagramEditor::fromXML(QDomElement &elem)
{
    static QMenu* menu = new QMenu;
    static QAction* act = menu->addAction("Удалить фрейм");
    QObject::connect(act, SIGNAL(triggered()),
                     SLOT(deleteSelectedNode()));
    if (elem.tagName() == "diagram") {
        QDomNodeList nodes = elem.childNodes();
        int count = nodes.count();
        for (int i = 0; i < count; ++i) {
            QDomElement e = nodes.at(i).toElement();
            if (e.tagName() == "item") {
                unsigned id = e.attribute("id").toUInt();
                QString title = e.attribute("title");
                qreal x = e.attribute("x").toDouble();
                qreal y = e.attribute("y").toDouble();
                DiagramItem* item = new DiagramItem(id, DiagramItem::TextRectangle, title, menu);
                item->setX(x);
                item->setY(y);
                m_items.insert(id, item);
                m_scene->addItem(item);
            } else if (e.tagName() == "link") {
                QString text = e.attribute("text");
                unsigned sid = e.attribute("sid").toUInt();
                unsigned did = e.attribute("did").toUInt();
                DiagramItem* start = m_items.value(sid, 0);
                DiagramItem* end = m_items.value(did, 0);
                static QMenu* menu = new QMenu;
                static QAction* act = menu->addAction("Удалить связь", this, SLOT(deleteSelectedLink()));
                Arrow* a = new Arrow(start, end, text, 0, m_scene);
                a->setContextMenu(menu);
                if (text == "is-a")
                    a->setColor(Qt::darkGreen);
                else if (text == "sub")
                    a->setColor(Qt::darkYellow);
                start->addArrow(a);
                end->addArrow(a);
                m_links << a;
                //m_scene->addItem(a);
            }
        }
    }
}

/* End of file lgen2diagrameditor.cpp */
