/* Begin of file: lgen2project.cpp */

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

#include "lgen2project.hpp"

LGen2Project::LGen2Project(QString name, QFile *file, QObject *parent) :
    QObject(parent), m_name(name), m_file(file),
    m_templateOntologyFile(0), m_domainOntologyFile(0)
{
    m_kb = new LKB;
}

bool LGen2Project::setDomainOntologyFromFile(QFile *file)
{
    m_kb->setDomainOntology(LOntologyManager::loadOWLXML(file));
    return m_kb->domainOntology();
 }

bool LGen2Project::setTemplateOntologyFromFile(QFile *file)
{
    m_kb->setTemplateOntology(LOntologyManager::loadOWLXML(file));
    return m_kb->templateOntology();
}

/* End of file: lgen2project.cpp */
