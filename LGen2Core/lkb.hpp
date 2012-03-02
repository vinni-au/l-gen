/* Begin of file: lkb.hpp */
#ifndef LKB_HPP
#define LKB_HPP

#include <QList>
#include <QHash>
#include "lnode.hpp"
#include "lontology.hpp"

class LKB
{
    LOntology* m_domainOntology;
    LOntology* m_templateOntology;

public:
    LKB(QString name, QString filename);

    LOntology* domainOntology() const
    {   return m_domainOntology;    }
    void setDomainOntology(LOntology* ontology)
    {   m_domainOntology = ontology;    }

    LOntology* templateOntology() const
    {   return m_templateOntology;  }
    void setTemplateOntology(LOntology* ontology)
    {   m_templateOntology = ontology;  }



private:
};

#endif // LKB_HPP
/* End of file: lkb.hpp */
