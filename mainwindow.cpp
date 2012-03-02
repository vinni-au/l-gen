/* Begin of file: mainwindow.cpp */
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_projectDockWidget->setVisible(false);

    m_domainOntologyWidget = new OntologyWidget;
    m_temlateOntologyWidget = new OntologyWidget;
    m_resultWidget = new ResultWidget(this);

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

/* End of file: lontology.cpp */
