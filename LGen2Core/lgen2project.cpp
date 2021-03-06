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
#include "3rdparty/QSugar/QSugar.hpp"

LGen2Project::LGen2Project(QString name, QFile *file, QObject *parent) :
    QObject(parent), m_name(name), m_file(file),
    m_templateOntologyFile(0), m_domainOntologyFile(0)
{
    m_kb = new LKB;
}

LGen2Project::~LGen2Project()
{
    delete m_kb;
    if (m_file)
        delete m_file;
    if (m_templateOntologyFile)
        delete m_templateOntologyFile;
    if (m_domainOntologyFile)
        delete m_domainOntologyFile;
}

bool LGen2Project::setDomainOntologyFromFile(QFile *file)
{
    m_domainOntologyFile = file;
    if (file->fileName().endsWith(".xml"))
        return m_kb->setDomainOntology(LOntologyManager::loadXML(file));
    else return m_kb->setDomainOntology(LOntologyManager::loadOWLXML(file));
}

bool LGen2Project::setTemplateOntologyFromFile(QFile *file)
{
    m_templateOntologyFile = file;
    if (file->fileName().endsWith(".xml"))
        return m_kb->setTemplateOntology(LOntologyManager::loadXML(file));
    return m_kb->setTemplateOntology(LOntologyManager::loadOWLXML(file));
}

void LGen2Project::save(LGen2DiagramEditor *doEditor, LGen2DiagramEditor *toEditor)
{
    QDomDocument xml =
        QXML"lgen2project"
            <"name"> m_name
            <"filename"> m_file->fileName();
    QDomDocument tempdoc = QXML"template"
                <"file"> m_templateOntologyFile->fileName();
    QDomDocument domain =  QXML"domain"
                <"file"> m_domainOntologyFile->fileName();

    if (doEditor)
        tempdoc << toEditor->toXML();
    if (toEditor)
        domain << doEditor->toXML();

    xml << tempdoc;
    xml << domain;

    if (m_file->open(QIODevice::WriteOnly))
        m_file->write(xml.toByteArray(4));
    m_file->close();

    LOntologyManager::saveXML(m_kb->domainOntology(), m_domainOntologyFile->fileName());
    LOntologyManager::saveXML(m_kb->templateOntology(), m_templateOntologyFile->fileName());
}

LGen2Project* LGen2Project::load(QString filename)
{
    LGen2Project* result = 0;

    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)) {
        QDomDocument xml = QXML(file.readAll());
        QDomNodeList nodes;
        QString name;
        QString filename;
        QString tfilename;
        QString dfilename;
        nodes = xml.elementsByTagName("name");
        if (nodes.count() == 1) {
            name = nodes.at(0).toElement().text().trimmed();
        } else return 0;

        nodes = xml.elementsByTagName("filename");
        if (nodes.count() == 1) {
            filename = nodes.at(0).toElement().text().trimmed();
        } else return 0;

        result = new LGen2Project(name, new QFile(filename));
        nodes = xml.elementsByTagName("template");
        if (nodes.count() == 1) {
            tfilename = nodes.at(0).toElement().firstChildElement("file").text().trimmed();
            result->m_templateDiagram = *(new QDomDocument("diagram"));
            result->m_templateDiagram.appendChild(nodes.at(0).childNodes().at(1));
        } else return 0;

        nodes = xml.elementsByTagName("domain");
        if (nodes.count() == 1) {
            dfilename = nodes.at(0).toElement().firstChildElement("file").text().trimmed();
            result->m_domainDiagram = *(new QDomDocument("diagram"));
            result->m_domainDiagram.appendChild(nodes.at(0).childNodes().at(1));
        } else return 0;

        if (!result->setTemplateOntologyFromFile(new QFile(tfilename))) {
            delete result;
            return 0;
        }
        if (!result->setDomainOntologyFromFile(new QFile(dfilename))) {
            delete result;
            return 0;
        }

        result->m_kb->setDomainOntology(LOntologyManager::loadXML(new QFile(dfilename)));
        result->m_kb->setTemplateOntology(LOntologyManager::loadXML(new QFile(tfilename)));
    }

    file.close();

    return result;
}

void LGen2Project::createEmptyDomainOntology(QString filename)
{
    QList< LNode* > nodes;
    LNode* root = new LNode("Thing", QList<LEdge*>(), 0);
    LNode* entity = new LNode("#сущность", QList<LEdge*>(), 0);
    LNode* situation = new LNode("#ситуация", QList<LEdge*>(), 0);
    LNode* action = new LNode("#действие", QList<LEdge*>(), 0);
    LNode* physicalEntity = new LNode("физическая сущность", QList<LEdge*>(), 0);
    LNode* abstractEntity = new LNode("абстрактная сущность", QList<LEdge*>(), 0);

    LEdge* edge1 = new LEdge("is-a", root, entity);
    LEdge* edge2 = new LEdge("has-subclass", entity, root);
    root->addEgde(edge2);
    entity->addEgde(edge1);

    edge1 = new LEdge("is-a", entity, physicalEntity);
    edge2 = new LEdge("has-subclass", physicalEntity, entity);
    entity->addEgde(edge2);
    physicalEntity->addEgde(edge1);


    edge1 = new LEdge("is-a", entity, abstractEntity);
    edge2 = new LEdge("has-subclass", abstractEntity, entity);
    entity->addEgde(edge2);
    abstractEntity->addEgde(edge1);


    edge1 = new LEdge("is-a", root, situation);
    edge2 = new LEdge("has-subclass", situation, root);
    root->addEgde(edge2);
    situation->addEgde(edge1);

    edge1 = new LEdge("is-a", root, action);
    edge2 = new LEdge("has-subclass", action, root);
    root->addEgde(edge2);
    action->addEgde(edge1);

    nodes << root << entity << situation << action << abstractEntity << physicalEntity;

    LOntology* ontology = new LOntology(root, nodes);
    m_kb->setDomainOntology(ontology);

    m_domainOntologyFile = new QFile(filename);
    m_domainOntologyFile->open(QIODevice::WriteOnly);
    m_domainOntologyFile->close();
}

void LGen2Project::createEmptyTemplateOntology(QString filename)
{
    QList< LNode* > nodes;
    LNode* root = new LNode("Thing", QList<LEdge*>(), 0);
    LNode* ttemp = new LNode("#шаблон задания", QList<LEdge*>(), 0);
    LNode* axiom = new LNode("#шаблон аксиом", QList<LEdge*>(), 0);
    LNode* answer = new LNode("#шаблон ответа", QList<LEdge*>(), 0);

    LEdge* edge1 = new LEdge("is-a", root, ttemp);
    LEdge* edge2 = new LEdge("has-subclass", ttemp, root);
    root->addEgde(edge2);
    ttemp->addEgde(edge1);

    edge1 = new LEdge("is-a", root, axiom);
    edge2 = new LEdge("has-subclass", axiom, root);
    root->addEgde(edge2);
    axiom->addEgde(edge1);

    edge1 = new LEdge("is-a", root, answer);
    edge2 = new LEdge("has-subclass", answer, root);
    root->addEgde(edge2);
    answer->addEgde(edge1);

    nodes << root << ttemp << axiom << answer;

    LOntology* ontology = new LOntology(root, nodes);
    m_kb->setTemplateOntology(ontology);

    m_templateOntologyFile = new QFile(filename);
    m_templateOntologyFile->open(QIODevice::WriteOnly);
    m_templateOntologyFile->close();
}
