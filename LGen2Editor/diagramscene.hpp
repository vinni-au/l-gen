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

//! Сцена - внутренне представление диаграммы
class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

    friend class LGen2DiagramEditor;

public:
    //! Режим работы сцены
    enum Mode {
        InsertItem, /*!< Вставка вершины */
        InsertLine, /*!< Вставка дуги */
        MoveItem    /*!< Перемещение элементов */
    };

    explicit DiagramScene(QMenu* itemMenu = 0, QObject *parent = 0);

    //! Установить режим работы
    void setMode(Mode mode)
    {   m_mode = mode;  }

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    //! Цвет текста
    QColor m_textColor;

    //! Цвет вершин
    QColor m_itemColor;

    //! Цвет дуг
    QColor m_lineColor;

    //! Контекстное меню
    QMenu* m_contextMenu;

    //! Текущий режим работы
    Mode m_mode;

    //! Тип создаваемых вершин
    DiagramItem::DiagramItemType m_itemType;

    //! Временная линия, рисуемая при рисовании стрелки
    QGraphicsLineItem* m_line;

signals:
    //! Извещает о том, что добавлена дуга
    void arrowAdded(Arrow* arrow);

};

#endif // DIAGRAMSCENE_HPP

/* End of file diagramscene.hpp */
