/* Begin of file diagramitem.hpp */

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

#ifndef DIAGRAMITEM_HPP
#define DIAGRAMITEM_HPP

#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "arrow.hpp"

//! Вершина диаграммы
class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 1 };

    //! Тип вершины
    enum DiagramItemType {
        TextRectangle /*!< Прямоугольник с текстом */
    };

    DiagramItem(DiagramItemType type = TextRectangle, QString text = QString(), QMenu* contextMenu = 0,
                QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    DiagramItem(quint64 id, DiagramItemType type = TextRectangle, QString text = QString(), QMenu* contextMenu = 0,
                QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    //! Удаляет дугу
    void removeArrow(Arrow *arrow);

    //! Удаляет все дуги
    void removeArrows();

    //! Удаляет дугу, ведущую в другую вершину
    void removeArrowTo(DiagramItem* item);

    //! Удаляет дугу, идущую из другой вершины
    void removeArrowFrom(DiagramItem* item);

    //! Возвращает тип вершины
    DiagramItemType diagramItemType() const
    {   return m_type;  }

    QPolygonF polygon() const
    {   return m_polygon;   }

    //! Добавить дугу
    void addArrow(Arrow *arrow);

    //! Возвращает список дуг
    QList<Arrow*> arrows()
    {   return m_arrows;    }

    QPixmap image() const;

    int type() const
    {   return Type;    }

    //! Возвращает внутренний идентификатор
    quint64 id() const
    {   return m_id;    }

    //! Возвращает текст
    QString text() const
    {   return m_text; }

    //! Задаёт текст для вершины
    void setText(QString text)
    {   m_text = text;    }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    //! Имитирует нажатие мыши на вершину
    /*!
      Используется для выделения вершины на сцене
    */
    void imitateMousePress();

private:
    //! Тип вершины
    DiagramItemType m_type;

    //! Полигон вершины
    QPolygonF m_polygon;

    //! Контекстное меню
    QMenu *m_contextMenu;

    //! Список дуг, выходящих из вершины и входящих в неё
    QList<Arrow *> m_arrows;

    //! Текст, сопутствующий вершине
    QString m_text;

    //! Внутренний идентификатор вершины
    quint64 m_id;

    void init();
};

#endif // DIAGRAMITEM_HPP

/* End of file diagramitem.hpp */
