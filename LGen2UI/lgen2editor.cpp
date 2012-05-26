#include "global.h"
#include "lgen2editor.hpp"
#include "ui_lgen2editor.h"

LGen2Editor::LGen2Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LGen2Editor)
{
    ui->setupUi(this);

    ui->toEditor->setCaseFramesVisible(false);
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

LGen2Editor::~LGen2Editor()
{
    delete ui;
}
