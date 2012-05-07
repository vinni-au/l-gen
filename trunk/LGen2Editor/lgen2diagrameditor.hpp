/* Begin of file lgen2diagrameditor.hpp */

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

#ifndef LGEN2DIAGRAMEDITOR_HPP
#define LGEN2DIAGRAMEDITOR_HPP

#include <QMap>
#include <QGraphicsView>
#include <QDomElement>
#include "diagramscene.hpp"

//! Редактор диаграмм
//TODO перенести часть интерфейса из DiagramScene
class LGen2DiagramEditor : public QGraphicsView
{
    Q_OBJECT

public:
    explicit LGen2DiagramEditor(QWidget *parent = 0, QMenu* contextMenu = 0);

    DiagramScene* scene() const
    {   return m_scene; }

    unsigned selectedFrameId();

    QDomElement toXML(QDomDocument &doc);
    void fromXML(QDomElement &doc);

    void setContextMenu(QMenu* menu)
    {   m_scene->m_contextMenu = menu;   }

    QColor textColor() const
    {   return m_scene->m_textColor; }
    void setTextColor(QColor color)
    {   m_scene->m_textColor = color;    }

    QColor itemColor() const
    {   return m_scene->m_itemColor; }
    void setItemColor(QColor color)
    {   m_scene->m_itemColor = color;    }

    QColor lineColor() const
    {   return m_scene->m_lineColor; }
    void setLineColor(QColor color)
    {   m_scene->m_lineColor = color;    }

    DiagramItem::DiagramItemType itemType() const
    {   return m_scene->m_itemType;  }
    void setItemType(DiagramItem::DiagramItemType type)
    {   m_scene->m_itemType = type;  }

private:
    //! Сцена
    DiagramScene* m_scene;

    //! Хэш-таблица вершин
    QHash<unsigned, DiagramItem*> m_items;

    //! Список дуг
    QList<Arrow*> m_links;

    //! Контекстное меню
    QMenu* m_contextMenu;

signals:
    //! Выделена вершина
    void nodeSelected(unsigned id);

    //! Запрос на удаление вершины
    void nodeDeleteRequest(unsigned id);

    //! Выделение снято
    void selectionCleared();

    //! Выделена дуга
    //TODO переделать на внутренний идентификатор дуги???
    void linkSelected(unsigned, unsigned);

    //TODO удалить эти сигналы
    void isaDeleted(unsigned sid, unsigned did);
    void apoDeleted(unsigned sid, unsigned did);

protected slots:
    //! Обработать изменение выделения
    void onSceneSelectionChanged();

    //! Удалить выделенную вершину
    void deleteSelectedNode();

    //! Удалить выделенную дугу
    void deleteSelectedLink();

    //! Удалить выделенные элементы
    void deleteSelectedItems();

public slots:
    //! Увеличить масштаб
    void zoomIn();

    //! Уменьшить масштаб
    void zoonOut();

    //! Добавить вершину
    void addNode(unsigned id, QString title);

    //! Изменить текст вершины
    void changeNodeText(unsigned id, QString newtitle);

    //! Удалить вершину
    void deleteNode(unsigned id);

    //Добавить связь между от вершины с идентификатором sid до вершины с идентификатором did
    //и надписью title
    //TODO
    void addLink(unsigned sid, unsigned did, QString title);
    void addArrow(Arrow* arrow);
    //Удалить связь
    void deleteLink(unsigned sid, unsigned did);

    //! Выделить вершину
    void selectNode(unsigned id);
    void selectLink(unsigned sid, unsigned did);

};

#endif // LGEN2DIAGRAMEDITOR_HPP

/* End of file lgen2diagrameditor.hpp */
