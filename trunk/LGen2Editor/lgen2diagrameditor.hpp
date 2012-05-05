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

private:
    DiagramScene* m_scene;

    QMap<unsigned, DiagramItem*> m_items;
    QList<Arrow*> m_links;


signals:
    void frameSelected(unsigned id);
    void nodeDeleted(unsigned id);
    void selectionCleared();
    void linkSelected(unsigned, unsigned);
    void isaDeleted(unsigned sid, unsigned did);
    void apoDeleted(unsigned sid, unsigned did);

protected slots:
    void sceneSelectionChanged();
    void deleteSelectedItem();
    void deleteSelectedLink();

public slots:
    void zoomIn();
    void zoonOut();
    //Добавить вершину с внутренним идентификатором id, надписью title, и типом type
    void addNode(unsigned id, QString title);
    void changeNodeTitle(unsigned id, QString newtitle);
    //Удалить вершин с внутренним идентификатором id
    void deleteNode(unsigned id);
    //Добавить связь между от вершины с идентификатором sid до вершины с идентификатором did
    //и надписью title
    void addLink(unsigned sid, unsigned did, QString title);
    void addArrow(Arrow* arrow);
    //Удалить связь
    void deleteLink(unsigned sid, unsigned did);

    void selectNode(unsigned id);
    void selectLink(unsigned sid, unsigned did);

};

#endif // LGEN2DIAGRAMEDITOR_HPP

/* End of file lgen2diagrameditor.hpp */
