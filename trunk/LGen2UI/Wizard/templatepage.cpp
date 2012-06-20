#include "templatepage.hpp"
#include "ui_templatepage.h"

TemplatePage::TemplatePage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::TemplatePage)
{
    ui->setupUi(this);
}

TemplatePage::~TemplatePage()
{
    delete ui;
}
