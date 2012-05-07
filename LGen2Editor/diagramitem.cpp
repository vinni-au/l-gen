/* Begin of file diagramitem.cpp */

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

#include "diagramitem.hpp"
#include "diagramscene.hpp"

DiagramItem::DiagramItem(unsigned id, DiagramItemType type, QString title, QMenu *contextMenu,
                         QGraphicsItem *parent, QGraphicsScene *scene) :
    QGraphicsPolygonItem(parent, scene), m_type(type), m_contextMenu(contextMenu),
    m_text(title), m_id(id)
{
    switch (m_type) {
        case TextRectangle:
        default:
            m_polygon << QPointF(-50, -25) << QPointF(-50, 25)
                      << QPointF(50, 25) << QPointF(50, -25)
                      << QPointF(-50, -25);
            break;
    }
    setPolygon(m_polygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void DiagramItem::removeArrow(Arrow *arrow)
{
    int index = m_arrows.indexOf(arrow);

    if (index != -1)
        m_arrows.removeAt(index);
}

void DiagramItem::removeArrows()
{
    Arrow *arrow = 0;
    for (int i = 0; i < m_arrows.count(); ++i) {
        arrow = m_arrows[i];
        if (arrow) {
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            scene()->removeItem(arrow);
            delete arrow;
        }
        arrow = 0;
    }
}

void DiagramItem::removeArrowTo(DiagramItem *item)
{
    foreach (Arrow* arrow, m_arrows) {
        if (arrow->endItem() == item) {
            DiagramScene* s = static_cast<DiagramScene*>(scene());
            if (s) {
                s->removeItem(arrow);
                m_arrows.removeAll(arrow);
                delete arrow;
            }
        }
    }
}

void DiagramItem::removeArrowFrom(DiagramItem *item)
{
    foreach (Arrow* arrow, m_arrows) {
        if (arrow->startItem() == item) {
            DiagramScene* s = static_cast<DiagramScene*>(scene());
            if (s) {
                s->removeItem(arrow);
                m_arrows.removeAll(arrow);
                delete arrow;
            }
        }
    }
}

void DiagramItem::addArrow(Arrow *arrow)
{
    m_arrows << arrow;
}

QPixmap DiagramItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(m_polygon);

    return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    if (m_contextMenu)
        m_contextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        Arrow* arrow;
        foreach (arrow, m_arrows) {
            arrow->updatePosition();
        }
    }

    return value;
}

void DiagramItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);
    //TODO написать нормальное построение прямоугольника
    painter->drawText(QRectF(-50, -25, 100, 50), Qt::AlignCenter, m_text);
    if (isSelected()) {
        painter->setBrush(QBrush(QColor(0, 0, 255, 40)));
        painter->drawPolygon(polygon());
    }
}

void DiagramItem::imitateMousePress()
{
    mousePressEvent(new QGraphicsSceneMouseEvent(QEvent::MouseButtonPress));
    mouseReleaseEvent(new QGraphicsSceneMouseEvent(QEvent::MouseButtonRelease));
}

/* End of file diagramitem.cpp */
