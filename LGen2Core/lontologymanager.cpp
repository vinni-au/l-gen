/* Begin of file: lontologymanager.cpp */

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

#include "lontologymanager.hpp"
#include "3rdparty/QSugar/QSugar.hpp"

LOntologyManager::LOntologyManager(QObject *parent) :
    QObject(parent)
{
}

LOntology* LOntologyManager::loadOWLXML(QFile *file)
{
    LOntology* result = 0;
    if (file->open(QIODevice::ReadOnly)) {
        QDomDocument doc;
        if (doc.setContent(file)) {
            QHash<QString, LNode*> nodesHash;
            QHash<QString, LEdge*> edgesHash;
            QHash<QString, LNode*> nodesHasParentHash;

            LNode* thing = new LNode("Thing");

            QDomElement root = doc.documentElement();
            if (root.tagName() == "Ontology") {
                QDomNodeList children = root.childNodes();
                int count = children.count();
                for (int i = 0; i < count; ++i) {
                    QDomElement current = children.at(i).toElement();
                    if (current.tagName() == "Declaration") {
                        QDomElement child = current.firstChildElement();
                        if (child.tagName() == "Class") {
                            QString iri = child.attribute("IRI").remove(0, 1);
                            LNode* node = new LNode(iri);
                            nodesHash[iri] = node;
                        }
                        if (child.tagName() == "ObjectProperty") {
                            QString iri = child.attribute("IRI").remove(0, 1);
                            LEdge* edge = new LEdge(iri, 0, 0);
                            edgesHash[iri] = edge;
                        }
                    }
                    if (current.tagName() == "EquivalentClasses") {
                        QDomNodeList chil = current.childNodes();
                        if (chil.count() == 2) {
                            QDomElement classElem = chil.at(0).toElement();
                            LNode* classNode = 0;
                            if (classElem.tagName() == "Class")
                                classNode = nodesHash.value(classElem.attribute("IRI").remove(0, 1), 0);
                            QDomElement second = chil.at(1).toElement();
                            if (second.tagName() == "ObjectSomeValuesFrom") {
                                QString link = second.firstChildElement("ObjectProperty").attribute("IRI").remove(0, 1);
                                QString to = second.firstChildElement("Class").attribute("IRI").remove(0, 1);
                                LNode* subnode = nodesHash.value(to, 0);
                                if (classNode && subnode) {
                                    LEdge* edge = new LEdge(link, subnode, classNode);
                                    LEdge* egde = new LEdge(link + "_reverse", classNode, subnode);
                                    classNode->addEgde(edge);
                                    subnode->addEgde(egde);
                                }
                            }
                            if (second.tagName() == "ObjectIntersectionOf") {
                                QDomNodeList list = second.childNodes();
                                for (int j = 0; j < list.count(); ++j) {
                                    QDomElement cel = list.at(j).toElement();
                                    if (cel.tagName() == "ObjectSomeValuesFrom") {
                                        QString link = cel.firstChildElement("ObjectProperty").attribute("IRI").remove(0, 1);
                                        QString to = cel.firstChildElement("Class").attribute("IRI").remove(0, 1);
                                        LNode* subnode = nodesHash.value(to, 0);
                                        if (classNode && subnode) {
                                            LEdge* edge = new LEdge(link, subnode, classNode);
                                            LEdge* egde = new LEdge(link + "_reverse", classNode, subnode);
                                            classNode->addEgde(edge);
                                            subnode->addEgde(egde);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (current.tagName() == "SubClassOf") {
                        QDomNodeList chil = current.childNodes();
                        if (chil.count() == 2) {
                            QDomElement classElem = chil.at(0).toElement();
                            LNode* node = 0;
                            if (classElem.tagName() == "Class")
                                node = nodesHash.value(classElem.attribute("IRI").remove(0, 1), 0);
                            QDomElement second = chil.at(1).toElement();
                            if (second.tagName() == "Class") {
                                nodesHasParentHash.insert(node->iri(), node);
                                LNode* snode = nodesHash.value(second.attribute("IRI").remove(0, 1));
                                if (snode && node) {
                                    LEdge* edge = new LEdge("is-a", snode, node);
                                    LEdge* egde = new LEdge("has-subclass", node, snode);
                                    node->addEgde(edge);
                                    snode->addEgde(egde);
                                }
                            }
                            if (second.tagName() == "ObjectSomeValuesFrom") {
                                QString link = second.firstChildElement("ObjectProperty").attribute("IRI").remove(0, 1);
                                QString to = second.firstChildElement("Class").attribute("IRI").remove(0, 1);
                                LNode* snode = nodesHash.value(to, 0);
                                if (node && snode) {
                                    LEdge* edge = new LEdge(link, snode, node);
                                    LEdge* egde = new LEdge(link + "_reverse", node, snode);
                                    node->addEgde(edge);
                                    snode->addEgde(egde);
                                }
                            }
                        }
                    }
                }
                QList<LNode*> values = nodesHash.values();
                count = values.count();
                for (int i = 0; i < count; ++i)
                    if (!nodesHasParentHash.value(values.at(i)->iri(), 0)) {
                        LNode* subnode = values.at(i);
                        LEdge* edge = new LEdge("is-a", thing, subnode);
                        LEdge* egde = new LEdge("has-subclass", subnode, thing);
                        thing->addEgde(egde);
                        subnode->addEgde(edge);
                    }
                values << thing;
                result = new LOntology(thing, values);
            }
        }
    }
    return result;
}

bool LOntologyManager::saveOWLXML(LOntology* ontology, QString filename)
{
    //TODO: write OWL/XML to file

    return false;
}

LOntology* LOntologyManager::loadXML(QFile *file)
{
    if (file->open(QIODevice::ReadOnly)) {
        QDomDocument doc;
        doc.setContent(file->readAll());
        LOntology* result = new LOntology(reinterpret_cast<LNode*>(0), QList<LNode*>());
        result->fromXML(doc);
        file->close();
    }
}

bool LOntologyManager::saveXML(LOntology *ontology, QString filename)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(ontology->toXML().toByteArray(4));
    file.close();
}

/* End of file: lontologymanager.cpp */
