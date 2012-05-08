#include "global.h"
#include "lgen2editor.hpp"
#include "ui_lgen2editor.h"

LGen2Editor::LGen2Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LGen2Editor)
{
    ui->setupUi(this);
}

LGen2Editor::~LGen2Editor()
{
    delete ui;
}
