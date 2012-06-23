#include "entitypage.hpp"
#include "ui_entitypage.h"
#include <QMessageBox>

EntityPage::EntityPage(LOntology *domainOntology, QWidget *parent) :
    QWizardPage(parent),
    m_ontology(domainOntology),
    ui(new Ui::EntityPage)
{
    ui->setupUi(this);

    m_model = new LOntologyModel;
    m_model->setOntology(domainOntology);
    m_model->setItemsCheckable(true);
    ui->treeView->setModel(m_model);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->expandAll();
    ui->treeView->collapseAll();
    ui->treeView->setRootIndex(m_model->indexFromIri("#сущность"));
}

bool EntityPage::validatePage()
{
    bool result = false;
    if (m_model->checkedNodes().count() == 1) {
        m_selectedNode = m_model->checkedNodes().at(0);
        if (m_selectedNode->isLeaf())
            result = true;
    }
    if (!result)
        QMessageBox::warning(this, "Внимание!", "Нужно выбрать одну сущность!");
    return result;
}

EntityPage::~EntityPage()
{
    delete ui;
}
