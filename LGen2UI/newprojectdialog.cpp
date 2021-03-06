/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This file is a part of L-Gen 2.0
 *
 * L-Gen 2.0 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * L-Gen 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "newprojectdialog.hpp"
#include "ui_newprojectdialog.h"
#include <QToolTip>
#include <QMessageBox>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog),
    m_doExists(false), m_toExists(false)
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
    fd.setNameFilters(QStringList() << "Онтология в формате XML (*.xml)"
                      << "Онтология в формате OWL/XML (*.owl)");
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
    fd.setNameFilters(QStringList() << "Онтология в формате XML (*.xml)"
                     <<"Онтология в формате OWL/XML (*.owl)");
    if (fd.exec()) {
        QString filename = fd.selectedFiles().at(0);
        ui->le_domain->setText(filename);
        m_domainFilename = filename;
    }
}

void NewProjectDialog::on_le_name_textEdited(const QString &arg1)
{
    ui->le_file->setText(QDir::toNativeSeparators(QDir::homePath() + QDir::separator() + arg1 + ".lgen"));
    ui->le_domain->setText(QDir::toNativeSeparators(QDir::homePath() + QDir::separator() + arg1 + "_DO.xml"));
    ui->le_template->setText(QDir::toNativeSeparators(QDir::homePath() + QDir::separator() + arg1 + "_TO.xml"));
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
    //TODO: detect whether files can be created
    m_projectname       = ui->le_name->text().simplified();
    m_filename          = ui->le_file->text().simplified();
    m_templateFilename  = ui->le_template->text().simplified();
    m_domainFilename    = ui->le_domain->text().simplified();
    m_toExists          = QFile::exists(m_templateFilename);
    m_doExists          = QFile::exists(m_domainFilename);

    if (m_projectname.isEmpty()) {
        showToolTipAtWidget(ui->le_name, "Имя проекта не может быть пустым");
        return false;
    }
    if (m_templateFilename.isEmpty()) {
        showToolTipAtWidget(ui->le_template, "Укажите файл с онтологией шаблонов задач");
        return false;
    }
    if (m_domainFilename.isEmpty()) {
        showToolTipAtWidget(ui->le_domain, "Укажите файл с онтологией предметной области");
        return false;
    }
    if (m_templateFilename == m_domainFilename) {
        showToolTipAtWidget(ui->le_domain, "Один и тот же файл не может содержать две онтологии!");
        return false;
    }
    if (!m_doExists || !m_toExists) {
        QString msg = "Файлы со следующими онтологиями не существуют: <ul>";
        if (!m_toExists)
            msg += "<li>онтология шаблонов задач</li>";
        if (!m_doExists)
            msg += "<li>онтология предметной области</li>";
        msg += "</ul>";
        msg += "<p>Обратите внимание, что в этом случае вышеперечисленные онтологии будут пустыми, "
               "и поэтому генерация текстов задач не будет работать.";
        QMessageBox::warning(this, "Внимание!", msg);
    }
    return true;
}

void NewProjectDialog::showToolTipAtWidget(QWidget *widget, QString text)
{
    QToolTip::showText(widget->rect().topLeft() + pos() + widget->pos(),
                       "<div style=\"background:white; color:red;\">" + text + "</div>", widget);
}
