/* Begin of file: lkb.hpp */

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

#ifndef LKB_HPP
#define LKB_HPP

#include <QList>
#include <QHash>
#include "lnode.hpp"
#include "lontology.hpp"

//! База знаний
class LKB
{
public:
    LKB();

    //! Возвращает указатель на онтологию предметной области
    /*!
      \sa m_domainOntology, setDomainOntology()
    */
    LOntology* domainOntology() const
    {   return m_domainOntology;    }

    //! Задаёт онтологию предментой области
    /*!
      \param ontology онтология предметной области
      \sa m_domainOntology, domainOntology()
    */
    // TODO: check ontology
    void setDomainOntology(LOntology* ontology)
    {   m_domainOntology = ontology;    }

    //! Возвращает указатель на онтологию шаблонов задач
    /*!
      \sa
    */
    LOntology* templateOntology() const
    {   return m_templateOntology;  }
    //! Задаёт онтологию шаблонов задач
    /*!
      \param ontology онтология шаблонов задач
      \sa m_templateOntology, templateOntology()
    */
    //TODO: check ontology
    void setTemplateOntology(LOntology* ontology)
    {   m_templateOntology = ontology;  }

private:
    //! Указатель на онтологию предметной области
    /*!
      \sa domainOntology(), setDomainOntology()
    */
    LOntology* m_domainOntology;

    //! Указатель на онтологию шаблонов задач
    /*!
      \sa templateOntology(), setTemplateOntology()
    */
    LOntology* m_templateOntology;
};

#endif // LKB_HPP
/* End of file: lkb.hpp */
