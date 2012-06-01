#include "situationdialog.hpp"
#include "ui_situationdialog.h"

SituationDialog::SituationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SituationDialog)
{
    ui->setupUi(this);
}

SituationDialog::~SituationDialog()
{
    delete ui;
}
