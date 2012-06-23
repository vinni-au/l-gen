#include "sentencedialog.hpp"
#include "ui_sentencedialog.h"

SentenceDialog::SentenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SentenceDialog)
{
    ui->setupUi(this);
}

SentenceDialog::~SentenceDialog()
{
    delete ui;
}
