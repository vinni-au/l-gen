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

#include "global.h"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "LGen2UI/lgen2editor.hpp"
#include <QCloseEvent>
#include <QMessageBox>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent /* = 0 */) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_project(0)
{
#ifdef DEBUG_CTOR
    qDebug() << NOW << "MainWindow сtor";
#endif

    ui->setupUi(this);

    QTreeView* projectTree = new QTreeView;
    projectTree->setHeaderHidden(true);
    ui->m_projectDockWidget->setWidget(projectTree);
    ui->m_projectDockWidget->setVisible(false);

    m_resultWidget          = new ResultWidget(this);

    m_editor = new LGen2Editor;

    m_domainModel   = new LOntologyModel;
    m_templateModel = new LOntologyModel;
    m_projectModel  = new LGen2ProjectModel;

    projectTree->setModel(m_projectModel);

    if (QApplication::instance()->argc() == 2) {
        QString path = QApplication::instance()->arguments().at(1);
        m_project = LGen2Project::load(path);
        if (m_project)
            loadProject(m_project);
    }

    QObject::connect(ui->act_ShowProjectTree, SIGNAL(triggered(bool)),
                     ui->m_projectDockWidget, SLOT(setVisible(bool)));
    QObject::connect(ui->act_Exit, SIGNAL(triggered()),
                     SLOT(close()));
}

MainWindow::~MainWindow()
{
#ifdef DEBUG_DTOR
    qDebug() << NOW << "MainWindow dtor";
#endif

    delete ui;
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
    // TODO: create empty project
    NewProjectDialog pd;
    if (pd.exec()) {
        bool needToCreate = false;
        LGen2Project* project = new LGen2Project(pd.name(), new QFile(pd.filename()));
        if (pd.domainFileExists()) {
            if (!project->setDomainOntologyFromFile(new QFile(pd.domainFilename()))) {
                QMessageBox::critical(this, "Ошибка", "Не удалось загрузить онтологию предметной области!");
                delete project;
                return;
            }
        } else needToCreate = true;
        if (needToCreate) {
            project->createEmptyDomainOntology(pd.domainFilename());
        }
        needToCreate = false;
        if (pd.templateFileExists()) {
            if (!project->setTemplateOntologyFromFile(new QFile(pd.templateFilename()))) {
                QMessageBox::critical(this, "Ошибка", "Не удалось загрузить онтологию шаблонов задач!");
                delete project;
                return;
            }
        } else needToCreate = true;
        if (needToCreate) {
            project->createEmptyTemplateOntology(pd.templateFilename());
        }
        closeProject();
        project->save();
        loadProject(project);
        setProperWindowCaption();

        setProjectRelatedMenusEnabled();
    }
}

void MainWindow::on_act_ProjectSave_triggered()
{
    if (m_project)
        m_project->save(m_editor->doEditor(), m_editor->toEditor());
}

void MainWindow::on_act_ProjectSaveAs_triggered()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setFilter("L-Gen 2.0 project (*.lgen)");
    if (fd.exec()) {
        m_project->setFilename(fd.selectedFiles().at(0));
        setProperWindowCaption();
    }
}

void MainWindow::on_act_ProjectOpen_triggered()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setFilter("L-Gen 2.0 project (*.lgen)");
    if (fd.exec()) {
        LGen2Project* project = LGen2Project::load(fd.selectedFiles().at(0));
        if (project) {
            closeProject();
            loadProject(project);
        }
    }
}

void MainWindow::on_act_ProjectClose_triggered()
{
    closeProject();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (userReallyWantsToQuit())
        event->accept();
    else event->ignore();
}

bool MainWindow::userReallyWantsToQuit()
{
    //TODO: check for changes
    bool quit = true;

    if (QMessageBox::question(this, "", "Вы действительно хотите выйти?", QMessageBox::Yes, QMessageBox::No)
            != QMessageBox::Yes)
        quit = false;

    return quit;
}

void MainWindow::closeProject()
{
    if (m_project) {
        //TODO: clean diagrams etc.

        m_projectModel->clear();

        m_editor->unloadProject();

        setCentralWidget(new QWidget);

        delete m_project;
        m_project = 0;
        setProperWindowCaption();
        setProjectRelatedMenusEnabled(false);
    }
}

void MainWindow::loadProject(LGen2Project *project)
{
    m_project = project;

    m_projectModel->setProject(m_project);

    m_templateModel->setOntology(project->kb()->templateOntology());
    m_domainModel->setOntology(project->kb()->domainOntology());

    // QMainWindow takes ownership of centralWidget
    m_editor = new LGen2Editor;
    m_editor->loadProject(m_project, m_templateModel, m_domainModel);


    setCentralWidget(m_editor);

    QTreeView* view = static_cast<QTreeView*>(ui->m_projectDockWidget->widget());
    if (view)
        view->expandAll();

    setProjectRelatedMenusEnabled();
}

void MainWindow::setProperWindowCaption()
{
    if (m_project)
        setWindowTitle("L-Gen 2.0 - [" + m_project->name() + "]");
    else setWindowTitle("L-Gen 2.0");
}

void MainWindow::setProjectRelatedMenusEnabled(bool enabled /* = true */)
{
    ui->act_ProjectSave->setEnabled(enabled);
    ui->act_ProjectSaveAs->setEnabled(enabled);
    ui->act_ProjectClose->setEnabled(enabled);
    ui->act_ShowOntoEditor->setEnabled(enabled);
    ui->act_ShowGenerator->setEnabled(enabled);
}
