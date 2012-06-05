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

#ifndef RESULTWIDGET_HPP
#define RESULTWIDGET_HPP

#include <QWidget>
#include "./../LGen2Core/linference.hpp"

class MainWindow;

namespace Ui {
    class ResultWidget;
}

class ResultWidget : public QWidget
{
    Q_OBJECT

    MainWindow* m_mainw;

public:
    ResultWidget(MainWindow* mainw, QWidget *parent = 0);
    ~ResultWidget();

private slots:
    void on_btn_generate_clicked();

private:
    Ui::ResultWidget *ui;
};

#include "./../mainwindow.hpp"

#endif // RESULTWIDGET_HPP
