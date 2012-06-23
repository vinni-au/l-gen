#include "linference.hpp"
#include "3rdparty/MCR/mcr.hpp"

LInference::LInference(QObject *parent) :
    QObject(parent)
{   }

QString LInference::generate(LNode *selectedTemplate, QList<LNode *> selectedEntities)
{
    QString result;
    QList<LNode*> cons;
    for (int i = 0; i < selectedTemplate->edges().count(); ++i) {
        if (selectedTemplate->edges().at(i)->name() == "APO_reverse" ||
                selectedTemplate->edges().at(i)->name() == "a_part_of_reverse") {
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
        result += templ[i]/*.replace("_", " ")*/
                    .replace("+"," - ") + "\n";
    LNode* selNode = selectedEntities.at(0);
    if (!selNode)
        return QString();

    LNode* situation = randomSituation(selNode->ontology());
            //selNode->ontology()->nodeFromIri("животные пьют жидкости");
    if (!situation)
        return QString();

    LNode* isaNode = isa(situation);
    if (!isaNode)
        return QString();

    LNode* action = 0;
    LNode* object = 0;
    while (!action || !object) {
        for (int i = 0; i < situation->edgesCount(); ++i) {
            if (situation->edges().at(i)->name() == "объект" && !object)
                object = peekDesc(situation->edges().at(i)->node(), QList<LNode*>() << isaNode << selNode);
            if (situation->edges().at(i)->name() == "действие" && !action)
                action = peekDesc(situation->edges().at(i)->node(), QList<LNode*>() << isaNode << selNode);
        }
        if (!action || ! object) {
            LEdge* edge = situation->edgeFromName("is-a");
            if (edge)
                situation = edge->node();
            else return QString();
        }
    }
    result.replace("*сущность*", selNode->iri())
            .replace("*агент(сущность)*", selNode->iri())
            .replace("*isa(сущность)*", isaNode->iri())
            .replace("*объект*", object->iri())
            .replace("*действие*", action->iri());
    return LInference::lemmatize(result);
}

LNode* LInference::situation(LNode *)
{
    return 0;
}

LNode* LInference::isa(LNode *situation)
{
    LNode* candidate = 0;
    QList<LNode*> totry;
    for (int i = 0; i < situation->edgesCount(); ++i)
        if (situation->edges().at(i)->name() == "агент")
            candidate =  situation->edges().at(i)->node();
    for (int i = 0; i < candidate->edgesCount(); ++i)
        if (candidate->edges().at(i)->name() == "has-subclass")
            totry << candidate->edges().at(i)->node();
    if (totry.count()) {
        LNode* node = totry.at(qrand() % totry.count());
        return node;
    } else {
        LNode* node = 0;
        node = LInference::peekDesc(candidate, QList<LNode*>() << candidate);
        return node;
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
    if (candidates.count())
        return candidates.at(qrand() % candidates.count());
    else return 0;
}

LNode* LInference::randomSituationFor(LNode *agent)
{
    QList<LEdge*> edges = agent->edgesFromName("агент_reverse");
    QList<LNode*> candidates;
    for (int i = 0; edges.count(); ++i) {
        candidates << edges.at(i)->node();
    }
    if (candidates.count())
        return candidates.at(qrand() % candidates.count());
    else return 0;
}

LNode* LInference::randomSituation(LOntology *ontology)
{
    LNode* situation = ontology->nodeFromIri("#ситуация");
    QList<LNode*> candidates;
    QList<LNode*> tosee;
    tosee << situation;
    while (tosee.count()) {
        QList<LNode*> torem;
        QList<LNode*> toapp;
        for (int i = 0; i < tosee.count(); ++i) {
            LNode* current = tosee.at(i);
            if (current->isLeaf())
                candidates << current;
            torem << current;
            toapp.append(current->children());
        }
        for (int i = 0; i < torem.count(); ++i)
            tosee.removeAll(torem.at(i));
        tosee.append(toapp);
    }
    if (candidates.count())
        return candidates.at(qrand() % candidates.count());
    else return 0;
}

QString LInference::lemmatize(QString source)
{
    QString result = source;
    QRegExp rx("\\(\\d+\\)[а-яА-Яa-zA-z]+");
    QStringList list;
    int pos = 0;
    while ((pos = rx.indexIn(source, pos)) != -1) {
        QString str = rx.cap(0);
        list << str;
        pos += rx.matchedLength();
    }

    MCR mcr;
    if (mcr.LoadVocabulary("./data/zal.mcr")) {

        for (int i = 0; i < list.count(); ++i) {
            QString current = list.at(i);
            QRegExp rx_num("\\(\\d+\\)");
            QRegExp rx_word("[а-яА-Яa-zA-z]+");
            rx_num.indexIn(current);
            rx_word.indexIn(current);
            QString num = rx_num.cap(0);
            QString word = rx_word.cap(0);
            num = num.mid(1, num.length() - 2);
            int vid = num.toInt();

            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QByteArray encoded = codec->fromUnicode(word);
            const char* w = encoded.constData();
            char* form = mcr.createWordForm(w, vid);
            QString sform = codec->toUnicode(form);
            result = result.replace(current, sform);
        }

    }

    return result;
}
