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

#ifndef LGEN2EDITOR_HPP
#define LGEN2EDITOR_HPP

#include <QWidget>
#include "LGen2MVC/lontologymodel.hpp"
#include "LGen2Core/lgen2project.hpp"

namespace Ui {
    class LGen2Editor;
}

class LGen2Editor : public QWidget
{
    Q_OBJECT

public:
    explicit LGen2Editor(QWidget *parent = 0);
    ~LGen2Editor();

    void loadModels(LOntologyModel* templateModel, LOntologyModel* domainModel);

    void loadProject(LGen2Project* project, LOntologyModel* templateModel, LOntologyModel* domainModel);
    void unloadProject();

    LGen2DiagramEditor* doEditor() const;
    LGen2DiagramEditor* toEditor() const;

private slots:
    void addNodeToDO(QString name);
    void addNodeToTO(QString name);

    void linkModeOnDO(QString name);
    void linkModeOnTO(QString name);

    void linkModeOffDO();
    void linkModeOffTO();

    void nodeAddedToDO(LNode* node);
    void edgeAddedToDO(LEdge* edge);

private:
    Ui::LGen2Editor *ui;

    LOntologyModel* m_domainModel;
    LOntologyModel* m_templateModel;

    LGen2Project* m_project;
};

#endif // LGEN2EDITOR_HPP
