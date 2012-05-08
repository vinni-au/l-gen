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
    ui->treeView->setModel(model);
    ui->treeView->update(QModelIndex());
}

/* End of file: ontologywidget.cpp */
