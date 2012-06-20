#include "entitypage.hpp"
#include "ui_entitypage.h"

EntityPage::EntityPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::EntityPage)
{
    ui->setupUi(this);
}

EntityPage::~EntityPage()
{
    delete ui;
}
