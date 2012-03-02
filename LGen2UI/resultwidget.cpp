/* Begin of file: resultwidget.cpp */
#include "resultwidget.hpp"
#include "ui_resultwidget.h"

ResultWidget::ResultWidget(MainWindow *mainw, QWidget *parent) :
    QWidget(parent), m_mainw(mainw),
    ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
}

ResultWidget::~ResultWidget()
{
    delete ui;
}

#include <QMessageBox>

void ResultWidget::on_btn_generate_clicked()
{
    if (m_mainw) {
        QList<LNode*> checkedTemplates = m_mainw->templateModel()->checkedNodes();
        if (checkedTemplates.count() == 1) {

        } else {
            QMessageBox::critical(this, "Внимание", "Нужно выбрать один шаблон задачи!");
            return;
        }
        QList<LNode*> checkedDomains = m_mainw->domainModel()->checkedNodes();
        if (checkedDomains.count() > 0) {
            ui->textEdit->setText(LInference::generate(checkedTemplates.at(0), checkedDomains));
        } else {
            QMessageBox::critical(this, "Внимание", "Нужно выбрать хотя бы одну сущность предметной области!");
        }
    }
}

/* End of file: resultwidget.cpp */
