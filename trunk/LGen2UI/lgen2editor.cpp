#include "lgen2editor.hpp"
#include "ui_lgen2editor.h"

LGen2Editor::LGen2Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LGen2Editor)
{
    ui->setupUi(this);

    ui->splitter->setSizes(QList<int>() << 1 << 7 << 1);
    ui->splitter_2->setSizes(QList<int>() << 1 << 7 << 1);

    //Запихнуть всё создание начальной БЗ в XMLину
    //TODO сделать нормальную генерацию айдишников
    ui->domainDiagram->addNode(0, "#Thing");
    ui->domainDiagram->addNode(1, "#Ситуация");
    ui->domainDiagram->addNode(2, "#Сущность");
    ui->domainDiagram->addNode(3, "#Действие");
    ui->domainDiagram->addLink(1, 0, "is-a");
    ui->domainDiagram->addLink(2, 0, "is-a");
    ui->domainDiagram->addLink(3, 0, "is-a");

    ui->templateDiagram->addNode(0, "#Thing");
    ui->templateDiagram->addNode(1, "#Шаблон");
    ui->templateDiagram->addLink(1, 0, "is-a");
}

LGen2Editor::~LGen2Editor()
{
    delete ui;
}
