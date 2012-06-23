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

#ifndef ONTOLOGYWIDGET_HPP
#define ONTOLOGYWIDGET_HPP

#include <QWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QTextEdit>
#include "LGen2MVC/lontologymodel.hpp"
#include "LGen2Editor/lgen2diagrameditor.hpp"
#include "LGen2Editor/lgen2objectpropertieseditor.hpp"
#include "categorizer.hpp"

namespace Ui {
    class OntologyWidget;
}

class OntologyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OntologyWidget(QWidget *parent = 0);
    ~OntologyWidget();

    void setModel(LOntologyModel* model);

    void setCategorizer(Categorizer* categorizer);

    LGen2DiagramEditor* diagramEditor() const;
    LGen2ObjectPropertiesEditor* treeView() const;

    bool acceptCommand(QString cmd);

private slots:
    void nodeChanged(LNode* node);

private:
    Ui::OntologyWidget *ui;

    Categorizer* m_categorizer;
};

#endif // ONTOLOGYWIDGET_HPP
