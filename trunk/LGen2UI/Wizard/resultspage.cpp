#include "resultspage.hpp"
#include "ui_resultspage.h"
#include "LGen2Core/linference.hpp"

ResultsPage::ResultsPage(TemplatePage *tp, EntityPage *ep, QWidget *parent) :
    QWizardPage(parent),
    m_templatePage(tp),
    m_entityPage(ep),
    ui(new Ui::ResultsPage)
{
    ui->setupUi(this);
}

void ResultsPage::initializePage()
{
    ui->textEdit->setText(LInference::generate(m_templatePage->selectedNode(),
                                               QList<LNode*>() << m_entityPage->selectedNode()));
}

ResultsPage::~ResultsPage()
{
    delete ui;
}

void ResultsPage::on_pushButton_2_clicked()
{
    ui->textEdit->setText(LInference::generate(m_templatePage->selectedNode(),
                                               QList<LNode*>() << m_entityPage->selectedNode()));
}
