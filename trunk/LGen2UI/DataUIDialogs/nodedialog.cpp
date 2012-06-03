#include "nodedialog.hpp"
#include "ui_nodedialog.h"
#include <QTreeView>

NodeDialog::NodeDialog(QString caption, LOntologyModel *ontologyModel,
                       QString parent, QString name) :
    ui(new Ui::NodeDialog)
{
    ui->setupUi(this);

    setWindowTitle(caption);

    QTreeView* view = new QTreeView;
    view->setHeaderHidden(true);
    ui->cbParent->setView(new QTreeView);

    ui->cbParent->setModel(ontologyModel);
    ui->leName->setText(name);

    QObject::connect(ui->btnCancel, SIGNAL(clicked()),
                     SLOT(reject()));
}

NodeDialog::~NodeDialog()
{
    delete ui;
}

void NodeDialog::on_btnAdd_clicked()
{

}

void NodeDialog::on_btnAddClose_clicked()
{

}
