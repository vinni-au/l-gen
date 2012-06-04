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

    // TODO: load categories from ontology
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
            docategorizer->addElementToCategory("#is-a", "Стандартные");
            docategorizer->addElementToCategory("#APO", "Стандартные");
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

    tocategorizer->addSection("Связи");
        tocategorizer->addCategoryToSection("Стандартные","Связи");
            tocategorizer->addElementToCategory("#is-a", "Стандартные");
            tocategorizer->addElementToCategory("#APO", "Стандартные");

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

// FIXME: that's temporary
struct tempedge
{
    quint64 id;
    quint64 sid;
    quint64 did;
    QString name;

    tempedge(quint64 i, quint64 s, quint64 d, QString n) : id(i), sid(s), did(d), name(n) {}
};

void LGen2Editor::loadProject(LGen2Project *project, LOntologyModel *templateModel, LOntologyModel *domainModel)
{
    m_project = project;
    loadModels(templateModel, domainModel);

    if (project->domainDiagram().isNull()) {
        LOntology* ontology = domainModel->ontology();
        QList< LNode* > nodes = ontology->nodes();
        QList< tempedge > edges;
        for (int i = 0; i < nodes.count(); ++i) {
            LNode* node = nodes.at(i);
            if (node->iri() != "Thing") {
                ui->doEditor->diagramEditor()->addNode(node->id(), node->iri());
                for (int j = 0; j < node->edges().count(); ++j) {
                    LEdge* edge = node->edges().at(j);
                    if (!edge->name().contains("_reverse") && edge->name() != "has-subclass")
                        edges << tempedge(edge->id(), node->id(), edge->node()->id(), edge->name());
                }
            }
        }
        for (int i = 0; i < edges.count(); ++i) {
            ui->doEditor->diagramEditor()->addLink(edges[i].id, edges[i].sid, edges[i].did, edges[i].name);
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
    if (name == "-") {
        ui->doEditor->diagramEditor()->zoomOut();
        return;
    }
    if (name == "+") {
        ui->doEditor->diagramEditor()->zoomIn();
        return;
    }
    if (name == "#сущность" || name == "#действие") {
        NodeDialog nd("Добавить вершину", m_domainModel, name);
        nd.exec();
        return;
    }
    if (name == "#ситуация") {
        SituationDialog sd;
        if (sd.exec()) {

        }
        return;
    }
}

void LGen2Editor::addNodeToTO(QString name)
{
    if (name == "-") {
        ui->toEditor->diagramEditor()->zoomOut();
        return;
    }
    if (name == "+") {
        ui->toEditor->diagramEditor()->zoomIn();
        return;
    }
}

void LGen2Editor::linkModeOnDO(QString name)
{
}

void LGen2Editor::linkModeOnTO(QString name)
{
}

void LGen2Editor::linkModeOffDO()
{
}

void LGen2Editor::linkModeOffTO()
{
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
    ui->doEditor->diagramEditor();
}

LGen2DiagramEditor* LGen2Editor::toEditor() const
{
    ui->toEditor->diagramEditor();
}

LGen2Editor::~LGen2Editor()
{
    delete ui;
}
