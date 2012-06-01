#include "edgedialog.hpp"
#include "ui_edgedialog.h"

EdgeDialog::EdgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdgeDialog)
{
    ui->setupUi(this);
}

EdgeDialog::~EdgeDialog()
{
    delete ui;
}
