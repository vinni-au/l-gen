#include "global.h"
#include "lgen2editor.hpp"
#include "ui_lgen2editor.h"
#include "DataUIDialogs/nodedialog.hpp"

LGen2Editor::LGen2Editor(QWidget *parent) :
    QWidget(parent), m_project(0),
    ui(new Ui::LGen2Editor)
{
    ui->setupUi(this);

    Categorizer* docategorizer = new Categorizer;

    // TODO: load categories from ontology
    docategorizer->addSection("Стандартные");
        docategorizer->addCategoryToSection("Вершины", "Стандартные");
            docategorizer->addElementToCategory("#Сущность","Вершины", false);
            docategorizer->addElementToCategory("#Действие","Вершины", false);
            docategorizer->addElementToCategory("#Ситуация","Вершины", false);
        docategorizer->addCategoryToSection("Связи","Стандартные");
            docategorizer->addElementToCategory("#is-a", "Связи");
            docategorizer->addElementToCategory("#APO", "Связи");
        docategorizer->addCategoryToSection("Падежные рамки", "Стандартные");
            docategorizer->addElementToCategory("Агент", "Падежные рамки");
            docategorizer->addElementToCategory("Реципиент", "Падежные рамки");
            docategorizer->addElementToCategory("Объект", "Падежные рамки");
            docategorizer->addElementToCategory("Действие", "Падежные рамки");

    ui->doEditor->setCategorizer(docategorizer);

    Categorizer* tocategorizer = new Categorizer;

    tocategorizer->addSection("Стандартные");
        tocategorizer->addCategoryToSection("Вершины", "Стандартные");
            tocategorizer->addElementToCategory("Вершина","Вершины", false);
        tocategorizer->addCategoryToSection("Связи","Стандартные");
            tocategorizer->addElementToCategory("is-a", "Связи");
            tocategorizer->addElementToCategory("a-part-of", "Связи");

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
}

// FIXME: that's temporary
struct tempedge
{
    quint64 sid;
    quint64 did;
    QString name;

    tempedge(quint64 s, quint64 d, QString n) : sid(s), did(d), name(n) {}
};

void LGen2Editor::loadProject(LGen2Project *project, LOntologyModel *templateModel, LOntologyModel *domainModel)
{
    m_project = project;
    loadModels(templateModel, domainModel);

    //TODO: load diagrams
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
                        edges << tempedge(node->id(), edge->node()->id(), edge->name());
                }
            }
        }
        for (int i = 0; i < edges.count(); ++i) {
            ui->doEditor->diagramEditor()->addLink(edges[i].sid, edges[i].did, edges[i].name);
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
}

void LGen2Editor::unloadProject()
{
    ui->toEditor->setModel(0);
    ui->doEditor->setModel(0);
}

void LGen2Editor::addNodeToDO(QString name)
{
    NodeDialog nd("Добавить вершину", m_domainModel);
    if (nd.exec()) {

    }
}

void LGen2Editor::addNodeToTO(QString name)
{
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

LGen2Editor::~LGen2Editor()
{
    delete ui;
}
