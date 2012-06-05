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

#ifndef ARROW_HPP
#define ARROW_HPP

#include <QGraphicsLineItem>
#include <QPainter>

class DiagramItem;

//! Стрелка на диаграмме
class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 2 };

    Arrow(DiagramItem *startItem, DiagramItem *endItem, QString text = QString(),
      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    Arrow(quint64 id, DiagramItem *startItem, DiagramItem *endItem, QString text = QString(),
      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    virtual int type() const
    {   return Type;    }

    //! Задаёт контекстное меню
    /*!
      \sa m_contextMenu
    */
    void setContextMenu(QMenu* menu)
    {   m_contextMenu = menu;   }

    //! Задаёт надпись
    /*!
      \sa m_text, text()
    */
    void setText(QString text)
    {   m_text = text;  }

    //! Возвращает надпись
    /*!
      \sa m_text, setText()
    */
    QString text() const
    {   return m_text;  }

    QRectF boundingRect() const;

    QPainterPath shape() const;

    //! Устанавливает цвет стрелки
    /*!
      \sa m_color
    */
    void setColor(const QColor &color)
    {   m_color = color;    }

    //! Возвращает указатель на вершину, из которой выходит дуга
    /*!
      \sa m_startItem
    */
    DiagramItem *startItem() const
    {   return m_startItem; }

    //! Возвращает указатель на вершнину, в которую входит дуга
    /*!
      \sa m_endItem
    */
    DiagramItem *endItem() const
    {   return m_endItem;   }

    //! Возвращает указатель на контекстное меню
    /*!
      \sa m_contextMenu, setContextMenu()
    */
    QMenu* contextMenu() const
    {   return m_contextMenu;   }

    //! Обновляет положение стрелки
    void updatePosition();

    quint64 id() const
    {   return m_id;    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget* widget = 0);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    //! Вершина, из которой выходит дуга
    /*!
      \sa startItem()
    */
    DiagramItem *m_startItem;

    //! Вершина, в которую входит дуга
    /*!
      \sa endItem()
    */
    DiagramItem *m_endItem;

    //! Цвет линии
    /*!
      \sa setColor()
    */
    QColor m_color;

    //! Полигон, представляющий острие стрелки
    QPolygonF m_arrowHead;

    //! Подпись на стрелке
    /*!
      \sa text(), setText()
    */
    QString m_text;

    //! Контекстное меню
    /*!
      \sa setContextMenu(), contextMenu()
    */
    QMenu* m_contextMenu;

    //! Внутренний идентификатор
    quint64 m_id;

    void init();

};

#include "diagramitem.hpp"

#endif // ARROW_HPP
