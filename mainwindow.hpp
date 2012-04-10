/* Begin of file: mainwindow.hpp */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QMdiSubWindow>
#include "LGen2UI/ontologywidget.hpp"
#include "LGen2UI/newprojectdialog.hpp"
#include "LGen2UI/resultwidget.hpp"
#include "LGen2UI/ontologyeditorwindow.hpp"
#include "LGen2Core/lgen2project.hpp"
#include "LGen2MVC/lontologymodel.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    LGen2Project* m_project;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    LOntologyModel* templateModel() const
    {   return m_templateModel; }
    LOntologyModel* domainModel() const
    {   return m_domainModel;   }

private slots:
    void on_act_Exit_triggered();
    void on_act_About_triggered();
    void on_act_AboutQt_triggered();
    void on_act_ProjectNew_triggered();

    void on_act_ShowProjectTree_triggered(bool checked);

    void on_act_ShowOntoEditor_triggered(bool checked);

private:
    Ui::MainWindow *ui;

    OntologyWidget* m_domainOntologyWidget;
    OntologyWidget* m_temlateOntologyWidget;
    ResultWidget* m_resultWidget;

    OntologyEditorWindow* m_ontologyWindow;

    LOntologyModel* m_templateModel;
    LOntologyModel* m_domainModel;
};

#endif // MAINWINDOW_HPP
/* End of file: mainwindow.hpp */
