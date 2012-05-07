/* Begin of file: mainwindow.cpp */

/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "LGen2UI/ontologyeditorwindow.hpp"
#include "LGen2UI/lgen2editor.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_projectDockWidget->setVisible(false);

    m_domainOntologyWidget = new OntologyWidget;
    m_temlateOntologyWidget = new OntologyWidget;
    m_resultWidget = new ResultWidget(this);

    m_ontologyWindow = new OntologyEditorWindow;

    m_domainModel = new LOntologyModel;
    m_templateModel = new LOntologyModel;

    QMdiSubWindow* win1 = new QMdiSubWindow(this);
    QMdiSubWindow* win2 = new QMdiSubWindow(this);
    QMdiSubWindow* win3 = new QMdiSubWindow(this);

    win1->setWidget(m_domainOntologyWidget);
    win2->setWidget(m_temlateOntologyWidget);
    win3->setWidget(m_resultWidget);

    ui->mdiArea->addSubWindow(win1);
    ui->mdiArea->addSubWindow(win2);
    ui->mdiArea->addSubWindow(win3);

    win1->hide();
    win2->hide();
    win3->hide();
/*
    QMdiSubWindow* win4 = new QMdiSubWindow(this);
    win4->setWidget(new LGen2Editor);
    win4->show();*/
    (new LGen2Editor)->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_act_Exit_triggered()
{
    close();
}

void MainWindow::on_act_About_triggered()
{
    QMessageBox::about(this, "О программe", "      L-Gen 2.0         ");
}

void MainWindow::on_act_AboutQt_triggered()
{
    QMessageBox::aboutQt(this, "O Qt");
}

void MainWindow::on_act_ProjectNew_triggered()
{
    NewProjectDialog pd;
    if (pd.exec()) {
        m_project = new LGen2Project(pd.name(), new QFile(pd.filename()));
        if (!m_project->setDomainOntologyFromFile(new QFile(pd.domainFilename())))
            QMessageBox::critical(this, "Ошибка", "Не удалось загрузить онтологию предметной области!");
        if (!m_project->setTemplateOntologyFromFile(new QFile(pd.templateFilename())))
            QMessageBox::critical(this, "Ошибка!", "Не удалось загрузить онтологию шаблонов задач!");
        m_domainModel->setOntology(m_project->kb()->domainOntology());
        m_domainOntologyWidget->setModel(m_domainModel);
        m_domainOntologyWidget->setWindowTitle("Предметная онтология");
        m_templateModel->setOntology(m_project->kb()->templateOntology());
        m_temlateOntologyWidget->setModel(m_templateModel);
        m_temlateOntologyWidget->setWindowTitle("Онтология шаблонов задач");
        m_resultWidget->setWindowTitle("Результат генерации");

        QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
        for (int i = 0; i < subWindows.count(); ++i)
            subWindows.at(i)->show();
    }
}

void MainWindow::on_act_ShowProjectTree_triggered(bool checked)
{
    ui->m_projectDockWidget->setVisible(checked);
}

void MainWindow::on_act_ShowOntoEditor_triggered(bool checked)
{
    m_ontologyWindow->setVisible(checked);
}

/* End of file: lontology.cpp */
