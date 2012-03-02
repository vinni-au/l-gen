/* Begin of file: lgen2project.cpp */
#include "lgen2project.hpp"

LGen2Project::LGen2Project(QString name, QFile *file, QObject *parent) :
    QObject(parent), m_name(name), m_file(file),
    m_templateOntologyFile(0), m_domainOntologyFile(0)
{
    m_kb = new LKB(name, file->fileName());
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
