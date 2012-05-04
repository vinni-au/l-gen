/* Begin of file diagramscene.hpp */

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

#ifndef DIAGRAMSCENE_HPP
#define DIAGRAMSCENE_HPP

#include <QMenu>
#include <QGraphicsScene>
#include "diagramitem.hpp"
#include "arrow.hpp"
#include <QGraphicsObject>

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, MoveItem};
    explicit DiagramScene(QMenu* itemMenu = 0, QObject *parent = 0);

    void setMode(Mode mode)
    {   m_mode = mode;  }

    QColor textColor() const
    {   return m_textColor; }
    void setTextColor(QColor color)
    {   m_textColor = color;    }

    QColor itemColor() const
    {   return m_itemColor; }
    void setItemColor(QColor color)
    {   m_itemColor = color;    }

    QColor lineColor() const
    {   return m_lineColor; }
    void setLineColor(QColor color)
    {   m_lineColor = color;    }

    void setItemMenu(QMenu* menu)
    {   m_itemMenu = menu;  }

    DiagramItem::DiagramItemType itemType() const
    {   return m_itemType;  }
    void setItemType(DiagramItem::DiagramItemType type)
    {   m_itemType = type;  }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QColor m_textColor;
    QColor m_itemColor;
    QColor m_lineColor;

    QMenu* m_itemMenu;

    Mode m_mode;

    DiagramItem::DiagramItemType m_itemType;

    QGraphicsLineItem* m_line;

signals:
    void arrowAdded(Arrow* arrow);

public slots:

};

#endif // DIAGRAMSCENE_HPP

/* End of file diagramscene.hpp */
