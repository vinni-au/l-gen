#include "ontologyeditorwindow.hpp"
#include "ui_ontologyeditorwindow.h"

OntologyEditorWindow::OntologyEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OntologyEditorWindow)
{
    ui->setupUi(this);
}

OntologyEditorWindow::~OntologyEditorWindow()
{
    delete ui;
}
