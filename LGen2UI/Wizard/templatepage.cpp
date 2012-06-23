#include <QMessageBox>
#include "templatepage.hpp"
#include "ui_templatepage.h"

TemplatePage::TemplatePage(LOntology* templateOntology, QWidget *parent) :
    QWizardPage(parent),
    m_ontology(templateOntology),
    ui(new Ui::TemplatePage)
{
    ui->setupUi(this);

    m_model = new LOntologyModel;
    m_model->setOntology(templateOntology);
    m_model->setItemsCheckable(true);
    ui->treeView->setModel(m_model);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->expandAll();
    ui->treeView->collapseAll();
    ui->treeView->setRootIndex(m_model->indexFromIri("#шаблон задания"));
    emit completeChanged();
}

bool TemplatePage::validatePage()
{
    bool result = false;
    if (m_model->checkedNodes().count() == 1) {
        m_selectedNode = m_model->checkedNodes().at(0);
        if (m_selectedNode->isLeaf())
            result = true;
    }
    if (!result)
        QMessageBox::warning(this, "Внимание!", "Нужно выбрать один шаблон задачи!");
    return result;
}

TemplatePage::~TemplatePage()
{
    delete ui;
}
