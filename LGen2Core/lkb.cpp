/* Begin of file: lkb.cpp */

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

#include "lkb.hpp"

LKB::LKB() :
    m_domainOntology(0), m_templateOntology(0)
{   }

// TODO: check ontology
bool LKB::setDomainOntology(LOntology *ontology)
{
    if (m_domainOntology)
        delete m_domainOntology;
    m_domainOntology = ontology;
    return true;
}

bool LKB::setTemplateOntology(LOntology *ontology)
{
    if (m_templateOntology)
        delete m_templateOntology;
    m_templateOntology = ontology;
    return true;
}


/* End of file: lkb.cpp */
