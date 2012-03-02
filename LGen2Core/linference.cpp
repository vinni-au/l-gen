/* Begin of file: linference.cpp */
#include "linference.hpp"

LInference::LInference(QObject *parent) :
    QObject(parent)
{   }

QString LInference::generate(LNode *selectedTemplate, QList<LNode *> selectedEntities)
{
    QString result;
    QList<LNode*> cons;
    for (int i = 0; i < selectedTemplate->edges().count(); ++i) {
        if (selectedTemplate->edges().at(i)->name() == "a_part_of_reverse") {
            cons << selectedTemplate->edges().at(i)->node();
        }
    }
    QList<LNode*> t;
    for (int i = 0; i < cons.count(); ++i)
        for (int j = 0; j < cons.at(i)->edgesCount(); ++j) {
            if (cons.at(i)->edges().at(j)->name() == "has-subclass")
                t << cons.at(i)->edges().at(j)->node();
        }
    QList<QString> templ;
    for (int i = 0; i < t.count(); ++i)
        for (int j = 0; j < t.at(i)->edgesCount(); ++j)
            if (t.at(i)->edges().at(j)->name() == "has-subclass")
                templ << t.at(i)->edges().at(j)->node()->iri();
    for (int i = 0; i < templ.count(); ++i)
        result += templ[i].replace("_", " ").replace("+"," - ") + "\n";
    LNode* selNode = selectedEntities.at(0);
    LNode* isaNode = isa(selNode);
    LNode* situation = selNode->ontology()->nodeFromIri("ситуация_пить");
    LNode* action = 0;
    LNode* object = 0;
    for (int i = 0; i < situation->edgesCount(); ++i) {
        if (situation->edges().at(i)->name() == "объект")
            object = peekDesc(situation->edges().at(i)->node(), QList<LNode*>() << isaNode << selNode);
        if (situation->edges().at(i)->name() == "действие")
            action = peekDesc(situation->edges().at(i)->node(), QList<LNode*>() << isaNode << selNode);
    }
    result.replace("*сущность*", selNode->iri())
            .replace("*агент(сущность)*", selNode->iri())
            .replace("*isa(сущность)*", isaNode->iri())
            .replace("*объект*", object->iri())
            .replace("*действие*", action->iri());
    return result;
}

LNode* LInference::situation(LNode *node)
{
    return 0;
}

LNode* LInference::isa(LNode *node)
{
    LNode* situation = node->ontology()->nodeFromIri("животные_пьют_жидкости");
    LNode* candidate = 0;
    QList<LNode*> totry;
    for (int i = 0; i < situation->edgesCount(); ++i)
        if (situation->edges().at(i)->name() == "агент")
            candidate =  situation->edges().at(i)->node();
    for (int i = 0; i < candidate->edgesCount(); ++i)
        if (candidate->edges().at(i)->name() == "has-subclass")
            totry << candidate->edges().at(i)->node();
    if (totry.count()) {
        return totry.at(qrand() % totry.count());
    }
    return 0;
}

LNode* LInference::peekDesc(LNode *node, QList<LNode *> forbidden)
{
    QList<LNode*> candidates;
    candidates << node;
    bool hasdesc = false;
    do {
        hasdesc = false;
        for (int j = 0; j < candidates.count(); ++j) {
            LNode* current = candidates.at(j);
            for (int i = 0; i < current->edgesCount(); ++i)
                if (!forbidden.contains(current->edges().at(i)->node()) &&
                        !candidates.contains(current->edges().at(i)->node()) &&
                        current->edges().at(i)->name() == "has-subclass")
                    candidates << current->edges().at(i)->node();
            if (!current->isLeaf())
                candidates.removeAll(current);
        }

        for (int i = 0; i < candidates.count(); ++i) {
            LNode* current = candidates.at(i);
            if (!current->isLeaf())
                hasdesc = true;
        }
    } while (hasdesc);
    return candidates.at(qrand() % candidates.count());
}

/* End of file: linference.cpp */
