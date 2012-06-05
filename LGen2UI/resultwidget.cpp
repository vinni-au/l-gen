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
