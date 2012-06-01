#include "global.h"
#include "lgen2editor.hpp"
#include "ui_lgen2editor.h"

LGen2Editor::LGen2Editor(QWidget *parent) :
    QWidget(parent),
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
    ui->toEditor->setModel(templateModel);
    ui->doEditor->setModel(domainModel);
}

void LGen2Editor::unloadModels()
{
    ui->toEditor->setModel(0);
    ui->doEditor->setModel(0);
}

void LGen2Editor::addNodeToDO(QString name)
{
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
