#include "generatorwizard.hpp"
#include "ui_generatorwizard.h"
#include "startpage.hpp"
#include "templatepage.hpp"
#include "finalpage.hpp"
#include "resultspage.hpp"
#include "entitypage.hpp"

GeneratorWizard::GeneratorWizard(LOntology *templateOntology,
                                 LOntology *domainOntology, QWidget *parent) :
    QWizard(parent),
    m_domainOnlotogy(domainOntology),
    m_templateOntology(templateOntology),
    ui(new Ui::GeneratorWizard)
{
    ui->setupUi(this);

    removePage(ui->wizardPage1->nextId());
    removePage(startId());

    addPage(new StartPage);
    TemplatePage* tp = new TemplatePage(templateOntology);
    EntityPage* ep = new EntityPage(domainOntology);
    addPage(tp);
    addPage(ep);
    addPage(new ResultsPage(tp, ep));
    addPage(new FinalPage);
}

GeneratorWizard::~GeneratorWizard()
{
    delete ui;
}
