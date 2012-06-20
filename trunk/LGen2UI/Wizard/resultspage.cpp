#include "resultspage.hpp"
#include "ui_resultspage.h"

ResultsPage::ResultsPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ResultsPage)
{
    ui->setupUi(this);
}

ResultsPage::~ResultsPage()
{
    delete ui;
}
