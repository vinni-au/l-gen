#include "ontologywidget.hpp"
#include "ui_ontologywidget.h"

OntologyWidget::OntologyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OntologyWidget), m_categorizer(0)
{
    ui->setupUi(this);
}

void OntologyWidget::setCategorizer(Categorizer *categorizer)
{
    if (m_categorizer)
        delete m_categorizer;

    m_categorizer = categorizer;
    ui->tabWidget->clear();
    m_categorizer->applyToTabWidget(ui->tabWidget);
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

LGen2DiagramEditor* OntologyWidget::diagramEditor() const
{
    return ui->graphicsView;
}
