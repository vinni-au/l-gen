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

#include "arrow.hpp"
#include <math.h>
#include <QGraphicsSceneContextMenuEvent>

const qreal Pi = 3.1415926535;

Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem,
             QString text, QGraphicsItem *parent,
             QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene), m_startItem(startItem),
      m_endItem(endItem), m_text(text), m_contextMenu(0), m_id(-1)
{
    init();
}

Arrow::Arrow(quint64 id, DiagramItem *startItem, DiagramItem *endItem,
             QString text, QGraphicsItem *parent,
             QGraphicsScene *scene) :
    m_id(id), QGraphicsLineItem(parent, scene), m_startItem(startItem),
    m_endItem(endItem), m_text(text), m_contextMenu(0)
{
    init();
}

void Arrow::init()
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    m_color = Qt::black;
    setPen(QPen(m_color, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    //TODO: add shape of text
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(m_arrowHead);
    return path;
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(m_startItem, 0, 0), mapFromItem(m_endItem, 0, 0));
    setLine(line);
}

void Arrow::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    if (m_contextMenu)
        m_contextMenu->exec(event->screenPos());
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
           QWidget *)
{
    if (m_startItem->collidesWithItem(m_endItem))
        return;

    QPen myPen = pen();
    myPen.setColor(m_color);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(m_color);
    QLineF centerLine(m_startItem->pos(), m_endItem->pos());

    QPolygonF endPolygon = m_endItem->polygon();
    QPointF p1 = endPolygon.first() + m_endItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + m_endItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);

        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    QPolygonF startPolygon = m_startItem->polygon();
    p1 = startPolygon.first() + m_startItem->pos();
    QPointF intersectPoint1;
    for (int i = 1; i < startPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + m_startItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint1);

        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }
    setLine(QLineF(intersectPoint, intersectPoint1));
    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                             cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                             cos(angle + Pi - Pi / 3) * arrowSize);

    m_arrowHead.clear();
    m_arrowHead << line().p1() << arrowP1 << arrowP2;

    if (isSelected())
        painter->setPen(QPen(m_color, 2, Qt::DotLine));

    painter->drawLine(line());
    painter->drawPolygon(m_arrowHead);

    int x = (m_startItem->pos().x() + m_endItem->pos().x()) / 2;
    int y = (m_startItem->pos().y() + m_endItem->pos().y()) / 2;
    painter->setPen(QPen(Qt::black, 3));
    painter->drawText(x, y, m_text);
}
