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

#include "global.h"
#include "lgen2editor.hpp"
#include "ui_lgen2editor.h"
#include "DataUIDialogs/nodedialog.hpp"
#include "DataUIDialogs/situationdialog.hpp"

LGen2Editor::LGen2Editor(QWidget *parent) :
    QWidget(parent), m_project(0),
    ui(new Ui::LGen2Editor)
{
    ui->setupUi(this);

    Categorizer* docategorizer = new Categorizer;

    // FIXME: load icons
    docategorizer->addSection("Стандартные");
        docategorizer->addCategoryToSection("Масштаб", "Стандартные");
            docategorizer->addElementToCategory("-", "Масштаб", false/*, new QIcon(":/pic/minus.png")*/);
            docategorizer->addElementToCategory("+", "Масштаб", false/*, new QIcon(":/pic/plus.png")*/);
        docategorizer->addCategoryToSection("Добавить вершину", "Стандартные");
            docategorizer->addElementToCategory("#сущность","Добавить вершину", false);
            docategorizer->addElementToCategory("#действие","Добавить вершину", false);
            docategorizer->addElementToCategory("#ситуация","Добавить вершину", false);
    docategorizer->addSection("Связи");
        docategorizer->addCategoryToSection("Стандартные","Связи");
            docategorizer->addElementToCategory("is-a", "Стандартные");
            docategorizer->addElementToCategory("APO", "Стандартные");
        docategorizer->addCategoryToSection("Падежные рамки", "Связи");
            docategorizer->addElementToCategory("Агент", "Падежные рамки");
            docategorizer->addElementToCategory("Реципиент", "Падежные рамки");
            docategorizer->addElementToCategory("Объект", "Падежные рамки");
            docategorizer->addElementToCategory("Действие", "Падежные рамки");

    ui->doEditor->setCategorizer(docategorizer);

    Categorizer* tocategorizer = new Categorizer;

    tocategorizer->addSection("Стандартные");
        tocategorizer->addCategoryToSection("Масштаб", "Стандартные");
            tocategorizer->addElementToCategory("-", "Масштаб", false/*, new QIcon(":/pic/minus.png")*/);
            tocategorizer->addElementToCategory("+", "Масштаб", false/*, new QIcon(":/pic/plus.png")*/);
        tocategorizer->addCategoryToSection("Добавить вершину", "Стандартные");
            tocategorizer->addElementToCategory("шаблон задания", "Добавить вершину", false);
            tocategorizer->addElementToCategory("шаблон аксиомы", "Добавить вершину", false);
            tocategorizer->addElementToCategory("шаблон ответа", "Добавить вершину", false);

    tocategorizer->addSection("Связи");
        tocategorizer->addCategoryToSection("Стандартные","Связи");
            tocategorizer->addElementToCategory("is-a", "Стандартные");
            tocategorizer->addElementToCategory("APO", "Стандартные");

    ui->toEditor->setCategorizer(tocategorizer);

    QObject::connect(docategorizer, SIGNAL(node(QString)),
                     SLOT(addNodeToDO(QString)));
    QObject::connect(docategorizer, SIGNAL(startLink(QString)),
                     SLOT(linkModeOnDO(QString)));
    QObject::connect(docategorizer, SIGNAL(endLink()),
                     SLOT(linkModeOffDO()));

    QObject::connect(tocategorizer, SIGNAL(node(QString)),
                     SLOT(addNodeToTO(QString)));
    QObject::connect(tocategorizer, SIGNAL(startLink(QString)),
                     SLOT(linkModeOnTO(QString)));
    QObject::connect(tocategorizer, SIGNAL(endLink()),
                     SLOT(linkModeOffTO()));

    QObject::connect(ui->doEditor->diagramEditor(), SIGNAL(addArrowRequest(quint64,quint64,QString)),
                     SLOT(addEdgeRequestToDO(quint64,quint64,QString)));
    QObject::connect(ui->toEditor->diagramEditor(), SIGNAL(addArrowRequest(quint64,quint64,QString)),
                     SLOT(addEdgeRequestToTO(quint64,quint64,QString)));
}

void LGen2Editor::loadModels(LOntologyModel *templateModel, LOntologyModel *domainModel)
{    
    ui->toEditor->setModel(m_templateModel = templateModel);
    ui->doEditor->setModel(m_domainModel = domainModel);

    QObject::connect(domainModel, SIGNAL(nodeAdded(LNode*)),
                     SLOT(nodeAddedToDO(LNode*)));
    QObject::connect(domainModel, SIGNAL(edgeAdded(LEdge*)),
                     SLOT(edgeAddedToDO(LEdge*)));
}

void LGen2Editor::loadProject(LGen2Project *project, LOntologyModel *templateModel, LOntologyModel *domainModel)
{
    m_project = project;
    loadModels(templateModel, domainModel);

    if (project->domainDiagram().isNull()) {
        LOntology* ontology = domainModel->ontology();
        QList< LNode* > nodes = ontology->nodes();
        for (int i = 0; i < nodes.count(); ++i) {
            LNode* node = nodes.at(i);
            if (node->iri() != "Thing") {
                ui->doEditor->diagramEditor()->addNode(node->id(), node->iri());
            }
        }

        QList< LEdge* > edges = ontology->edges();
        for (int i = 0; i < edges.count(); ++i) {
            LEdge* edge = edges.at(i);
            if (edge->name() != "has-subclass" && !edge->name().contains("_reverse"))
                if (edge->source()->iri() != "Thing" && edge->node()->iri() != "Thing")
                    ui->doEditor->diagramEditor()->addLink(
                                edge->id(), edge->source()->id(),
                                edge->node()->id(), edge->name());
        }
    }

    if (project->templateDiagram().isNull()) {
        LOntology* ontology = templateModel->ontology();
        QList< LNode* > nodes = ontology->nodes();
        for (int i = 0; i < nodes.count(); ++i) {
            LNode* node = nodes.at(i);
            if (node->iri() != "Thing")
                ui->toEditor->diagramEditor()->addNode(node->id(), node->iri());
        }

    }

    ui->doEditor->diagramEditor()->fromXML(project->domainDiagram().documentElement());
    ui->toEditor->diagramEditor()->fromXML(project->templateDiagram().documentElement());
}

void LGen2Editor::unloadProject()
{
    ui->toEditor->setModel(0);
    ui->doEditor->setModel(0);
}

void LGen2Editor::addNodeToDO(QString name)
{
    if (ui->doEditor->acceptCommand(name))
        return;
    if (name == "#сущность" || name == "#действие") {
        NodeDialog nd("Добавить вершину", m_domainModel, name);
        nd.exec();
        return;
    }
    if (name == "#ситуация") {
        SituationDialog sd("Добавить ситуацию", m_domainModel);
        sd.exec();
        return;
    }
}

void LGen2Editor::addNodeToTO(QString name)
{
    if (ui->toEditor->acceptCommand(name))
        return;
}

void LGen2Editor::linkModeOnDO(QString name)
{
    ui->doEditor->diagramEditor()->scene()->setMode(DiagramScene::InsertLine);
    ui->doEditor->diagramEditor()->scene()->setLinkTitle(name);
}

void LGen2Editor::linkModeOnTO(QString name)
{
    ui->toEditor->diagramEditor()->scene()->setMode(DiagramScene::InsertLine);
    ui->toEditor->diagramEditor()->scene()->setLinkTitle(name);
}

void LGen2Editor::linkModeOffDO()
{
    ui->doEditor->diagramEditor()->scene()->setMode(DiagramScene::MoveItem);
}

void LGen2Editor::linkModeOffTO()
{
    ui->toEditor->diagramEditor()->scene()->setMode(DiagramScene::MoveItem);
}

void LGen2Editor::addEdgeRequestToDO(quint64 sid, quint64 did, QString title)
{
    if (!title.isEmpty())
        m_domainModel->insertEdge(sid, did, title);
}

void LGen2Editor::addEdgeRequestToTO(quint64 sid, quint64 did, QString title)
{
    if (!title.isEmpty())
        m_templateModel->insertEdge(sid, did, title);
}

void LGen2Editor::nodeAddedToDO(LNode *node)
{
    ui->doEditor->diagramEditor()->addNode(node->id(), node->iri());
}

void LGen2Editor::edgeAddedToDO(LEdge *edge)
{
    ui->doEditor->diagramEditor()->addLink(edge->id(), edge->source()->id(), edge->node()->id(), edge->name());
}

LGen2DiagramEditor* LGen2Editor::doEditor() const
{
    return ui->doEditor->diagramEditor();
}

LGen2DiagramEditor* LGen2Editor::toEditor() const
{
    return ui->toEditor->diagramEditor();
}

LGen2Editor::~LGen2Editor()
{
    delete ui;
}
