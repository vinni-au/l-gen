#include "situationdialog.hpp"
#include "ui_situationdialog.h"

SituationDialog::SituationDialog(QString caption, LOntologyModel *model,
                                 QString parent, QString name) :
    ui(new Ui::SituationDialog),
    m_model(model)
{
    ui->setupUi(this);
    setWindowTitle(caption);

    ui->leName->setText(name);

    ui->cbParent->showPopup();
    if (!parent.isEmpty())
        ui->cbParent->view()->setCurrentIndex(model->indexFromIri(parent));

    m_timerId = startTimer(300);

    QObject::connect(ui->btnCancel, SIGNAL(clicked()),
                     SLOT(reject()));
}

SituationDialog::~SituationDialog()
{
    delete ui;
}

void SituationDialog::on_btnAdd_clicked()
{
    if (!ui->leName->text().isEmpty())
        if (ui->cbParent->view()->selectionModel()->selectedIndexes().count() == 1) {
            //Добавить вершину ситуации
            m_model->insertNodeOn(ui->cbParent->view()->selectionModel()->selectedIndexes().at(0),
                                  ui->leName->text());
            //TODO: add edges
        }
    ui->leName->setText("");
}

void SituationDialog::on_btnAddClose_clicked()
{
    on_btnAdd_clicked();
    accept();
}

void SituationDialog::timerEvent(QTimerEvent *)
{
    killTimer(m_timerId);
    ui->cbParent->hidePopup();
    ui->cbParent->hidePopup();
    ui->leName->setFocus();
}
