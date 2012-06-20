#include "nodedialog.hpp"
#include "ui_nodedialog.h"
#include <QTreeView>
#include <QMouseEvent>

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
        ui->cbParent->view()->setCurrentIndex(ontologyModel->indexFromIri(parent));
    }
    m_timerId = startTimer(300);

    QObject::connect(ui->btnCancel, SIGNAL(clicked()),
                     SLOT(reject()));
}

NodeDialog::~NodeDialog()
{
    delete ui;
}

void NodeDialog::on_btnAdd_clicked()
{
    QString parent;
    if (!ui->leName->text().isEmpty()) {
        if (ui->cbParent->view()->selectionModel()->selectedIndexes().count() == 1) {
            parent = ui->cbParent->currentText();
            m_model->insertNodeOn(ui->cbParent->view()->selectionModel()->selectedIndexes().at(0),
                                  ui->leName->text());
        }
    }
    ui->leName->setText("");
    ui->cbParent->showPopup();
    if (!parent.isEmpty())
        ui->cbParent->view()->setCurrentIndex(m_model->indexFromIri(parent));
    m_timerId = startTimer(150);
}

void NodeDialog::on_btnAddClose_clicked()
{
    on_btnAdd_clicked();
    accept();
}

void NodeDialog::timerEvent(QTimerEvent *)
{
    killTimer(m_timerId);
    ui->cbParent->hidePopup();
    ui->cbParent->hidePopup();
    ui->leName->setFocus();
}
