#include "generatorwizard.hpp"
#include "ui_generatorwizard.h"
#include "startpage.hpp"
#include "templatepage.hpp"
#include "finalpage.hpp"

GeneratorWizard::GeneratorWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::GeneratorWizard)
{
    ui->setupUi(this);

    removePage(ui->wizardPage1->nextId());
    removePage(startId());

    addPage(new StartPage);
    addPage(new TemplatePage);
    addPage(new FinalPage);
}

GeneratorWizard::~GeneratorWizard()
{
    delete ui;
}
