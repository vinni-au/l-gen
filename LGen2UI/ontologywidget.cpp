/* Begin of file: ontologywidget.cpp */
#include "ontologywidget.hpp"
#include "ui_ontologywidget.h"

OntologyWidget::OntologyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OntologyWidget)
{
    ui->setupUi(this);

    ui->splitter->setSizes(QList<int>() << 1 << 4);
}

OntologyWidget::~OntologyWidget()
{
    delete ui;
}

void OntologyWidget::setModel(LOntologyModel *model)
{
    QItemSelectionModel* smodel = ui->treeView->selectionModel();
    ui->treeView->setModel(model);
    delete smodel;
    ui->treeView->update(QModelIndex());
}

void OntologyWidget::setCaseFramesVisible(bool visible /* = true */)
{
    ui->caseframesFrame->setVisible(visible);
    ui->caseframesLabel->setVisible(visible);
}

/* End of file: ontologywidget.cpp */
