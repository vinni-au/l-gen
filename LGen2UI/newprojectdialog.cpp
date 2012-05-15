/* Begin of file: newprojectdialog.cpp */
#include "newprojectdialog.hpp"
#include "ui_newprojectdialog.h"
#include <QToolTip>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::on_btn_file_clicked()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setNameFilter("Проект L-Gen 2.0 (*.lgen)");
    if (fd.exec()) {
        QString filename = fd.selectedFiles().at(0);
        ui->le_file->setText(filename);
        m_filename = filename;
    }
}

void NewProjectDialog::on_btn_template_clicked()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setNameFilter("Онтология в формате OWL/XML (*.owl)");
    if (fd.exec()) {
        QString filename = fd.selectedFiles().at(0);
        ui->le_template->setText(filename);
        m_templateFilename = filename;
    }
}

void NewProjectDialog::on_btn_domain_clicked()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setNameFilter("Онтология в формате OWL/XML (*.owl)");
    if (fd.exec()) {
        QString filename = fd.selectedFiles().at(0);
        ui->le_domain->setText(filename);
        m_domainFilename = filename;
    }
}

void NewProjectDialog::on_le_name_textEdited(const QString &arg1)
{
    ui->le_file->setText(QDir::homePath() + QDir::separator() + arg1 + ".lgen");
}

void NewProjectDialog::on_btn_ok_clicked()
{
    if (checkData())
        accept();
}

void NewProjectDialog::on_btn_cancel_clicked()
{
    reject();
}

bool NewProjectDialog::checkData()
{
    m_projectname = ui->le_name->text().simplified();
    m_filename = ui->le_file->text().simplified();
    m_templateFilename = ui->le_template->text().simplified();
    m_domainFilename = ui->le_domain->text().simplified();
    if (!QFile::exists(m_templateFilename)) {
        showToolTipAtWidget(ui->le_template, "Указанный файл не существует");
        return false;
    }
    if (!QFile::exists(m_domainFilename)) {
        showToolTipAtWidget(ui->le_domain, "Указанный файл не существует");
        return false;
    }
    if (m_projectname.isEmpty()) {
        showToolTipAtWidget(ui->le_name, "Имя проекта не может быть пустым");
        return false;
    }
    return true;
}

void NewProjectDialog::showToolTipAtWidget(QWidget *widget, QString text)
{
    QToolTip::showText(widget->rect().topLeft() + pos() + widget->pos(),
                       "<div style=\"background:white; color:red;\">" + text + "</div>", widget);
}

/* End of file: newprojectdialog.cpp */
