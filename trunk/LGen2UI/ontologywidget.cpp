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

#include "ontologywidget.hpp"
#include "ui_ontologywidget.h"

OntologyWidget::OntologyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OntologyWidget), m_categorizer(0)
{
    ui->setupUi(this);

    QObject::connect(ui->graphicsView, SIGNAL(nodeSelected(quint64)),
                     ui->treeView, SLOT(selectNode(quint64)));
    QObject::connect(ui->treeView, SIGNAL(nodeSelected(quint64)),
                     ui->graphicsView, SLOT(selectNode(quint64)));
}

void OntologyWidget::setCategorizer(Categorizer *categorizer)
{
    if (m_categorizer)
        delete m_categorizer;

    m_categorizer = categorizer;
    ui->tabWidget->clear();
    m_categorizer->applyToTabWidget(ui->tabWidget);
}

OntologyWidget::~OntologyWidget()
{
    delete ui;
}

void OntologyWidget::setModel(LOntologyModel *model)
{
    QItemSelectionModel* smodel = ui->treeView->selectionModel();
    ui->treeView->setModel(model);
    delete smodel;
    ui->treeView->update(QModelIndex());
}

LGen2DiagramEditor* OntologyWidget::diagramEditor() const
{
    return ui->graphicsView;
}

bool OntologyWidget::acceptCommand(QString cmd)
{
    if (cmd == "-") {
        ui->graphicsView->zoomOut();
        return true;
    }
    if (cmd == "+") {
        ui->graphicsView->zoomIn();
        return true;
    }
    return false;
}
