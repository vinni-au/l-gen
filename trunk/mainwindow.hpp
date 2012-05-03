/* Begin of file: mainwindow.hpp */

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

//! Класс главного окна приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

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
    //! Интерфейс пользователя
    Ui::MainWindow *ui;

    //! Окно онтологии предметной области
    OntologyWidget* m_domainOntologyWidget;
    //! Окно онтологии шаблонов задач
    OntologyWidget* m_temlateOntologyWidget;
    //! Окно результата генерации
    ResultWidget* m_resultWidget;

    //! Окно редактора онтологии
    OntologyEditorWindow* m_ontologyWindow;
    //! Модель шаблонов задач
    LOntologyModel* m_templateModel;
    //! Модель понятий предметной области
    LOntologyModel* m_domainModel;

    //! Текущий проект, с которым идёт работа
    LGen2Project* m_project;

};

#endif // MAINWINDOW_HPP
/* End of file: mainwindow.hpp */
