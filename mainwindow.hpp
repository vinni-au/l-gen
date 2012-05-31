/* Begin of file: mainwindow.hpp */

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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QMdiSubWindow>
#include "LGen2UI/ontologywidget.hpp"
#include "LGen2UI/newprojectdialog.hpp"
#include "LGen2UI/resultwidget.hpp"
#include "LGen2UI/lgen2editor.hpp"
#include "LGen2Core/lgen2project.hpp"
#include "LGen2MVC/lontologymodel.hpp"
#include "LGen2MVC/lgen2projectmodel.hpp"

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

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_act_About_triggered();
    void on_act_AboutQt_triggered();
    void on_act_ProjectNew_triggered();
    void on_act_ProjectSave_triggered();
    void on_act_ProjectSaveAs_triggered();
    void on_act_ProjectOpen_triggered();
    void on_act_ProjectClose_triggered();

private:
    //! Интерфейс пользователя
    Ui::MainWindow* ui;

    //! Окно результата генерации
    ResultWidget*       m_resultWidget;

    //! Окно редактора онтологии
    LGen2Editor*        m_editor;

    //! Модель шаблонов задач
    LOntologyModel*     m_templateModel;

    //! Модель понятий предметной области
    LOntologyModel*     m_domainModel;

    //! Модель дерева проекта
    LGen2ProjectModel*  m_projectModel;

    //! Текущий проект, с которым идёт работа
    LGen2Project*       m_project;

    bool userReallyWantsToQuit();

    void closeProject();
    void loadProject(LGen2Project* project);
    void setProperWindowCaption();
    void setProjectRelatedMenusEnabled(bool enabled = true);

};

#endif // MAINWINDOW_HPP
/* End of file: mainwindow.hpp */
