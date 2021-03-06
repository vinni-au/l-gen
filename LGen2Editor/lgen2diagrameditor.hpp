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
class LGen2DiagramEditor : public QGraphicsView
{
    Q_OBJECT

public:
    explicit LGen2DiagramEditor(QWidget *parent = 0, QMenu* contextMenu = 0);

    DiagramScene* scene() const
    {   return m_scene; }

    unsigned selectedFrameId();

    QDomElement toXML(QDomDocument &doc);
    QDomDocument toXML();
    void fromXML(QDomElement doc);

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

    void setAppropriateColors(Arrow* a);

signals:
    //! Выделена вершина
    void nodeSelected(quint64 id);

    //! Запрос на удаление вершины
    void nodeDeleteRequest(quint64 id);

    //! Выделение снято
    void selectionCleared();

    //! Выделена дуга
    void linkSelected(quint64 sid, quint64 did);

    //! Выделена дуга
    void linkSelected(quint64 id);

    //! Запрос на добавление дуги
    void addArrowRequest(quint64 source, quint64 dest, QString title);

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
    void zoomOut();

    //! Добавить вершину
    void addNode(quint64 id, QString title);

    //! Изменить текст вершины
    void changeNodeText(quint64 id, QString newtitle);

    //! Удалить вершину
    void deleteNode(quint64 id);

    //! Добавить связь между от вершины с идентификатором sid до вершины с идентификатором did и надписью title
    void addLink(quint64 id, quint64 sid, quint64 did, QString title);

    //TODO: change to link's identifier?
    void addArrow(Arrow* arrow);

    //! Удалить связь
    void deleteLink(quint64 sid, quint64 did);

    //! Выделить вершину
    void selectNode(quint64 id);

    //! Снять выделение
    void clearSelection();

};

#endif // LGEN2DIAGRAMEDITOR_HPP

/* End of file lgen2diagrameditor.hpp */
