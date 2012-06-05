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

#ifndef LONTOLOGYMANAGER_HPP
#define LONTOLOGYMANAGER_HPP

#include <QObject>
#include <QDomDocument>
#include <QFile>
#include <QHash>
#include "lnode.hpp"
#include "lontology.hpp"

//! Менеджер онтологической БЗ
class LOntologyManager : public QObject
{
    Q_OBJECT
public:
    explicit LOntologyManager(QObject *parent = 0);

    //! Загружает онтологию в формате OWL/XML из файла
    /*!
      \param file Входной файл с онтологией
    */
    static LOntology* loadOWLXML(QFile* file);

    //! Сохраняет онтологию в формате OWL/XML
    /*!
      \param filename Путь к файлу
    */
    static bool saveOWLXML(LOntology* ontology, QString filename);

    static LOntology* loadXML(QFile* file);
    static bool saveXML(LOntology* ontology, QString filename);
    static bool saveXML(LOntology *ontology, QFile* file);

signals:

public slots:

};

#endif // LONTOLOGYMANAGER_HPP
