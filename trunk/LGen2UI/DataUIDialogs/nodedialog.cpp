#include "nodedialog.hpp"
#include "ui_nodedialog.h"
#include <QTreeView>

NodeDialog::NodeDialog(QString caption, LOntologyModel *ontologyModel,
                       QString parent, QString name) :
    ui(new Ui::NodeDialog), m_model(ontologyModel)
{
    ui->setupUi(this);

    setWindowTitle(caption);


    ui->cbParent->setModel(ontologyModel);
    ui->leName->setText(name);

    ui->cbParent->showPopup();
    if (!parent.isEmpty()) {
        ui->cbParent->view()->selectionModel()->setCurrentIndex(ontologyModel->indexFromIri(parent), QItemSelectionModel::Select);
    }
    ui->cbParent->hidePopup();

    QObject::connect(ui->btnCancel, SIGNAL(clicked()),
                     SLOT(reject()));
}

NodeDialog::~NodeDialog()
{
    delete ui;
}

void NodeDialog::on_btnAdd_clicked()
{
    if (!ui->leName->text().isEmpty()) {
        if (ui->cbParent->view()->selectionModel()->selectedIndexes().count() == 1)
            m_model->insertNodeOn(ui->cbParent->view()->selectionModel()->selectedIndexes().at(0), ui->leName->text());
    }
}

void NodeDialog::on_btnAddClose_clicked()
{
    on_btnAdd_clicked();
    accept();
}
