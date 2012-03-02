/* Begin of file: linference.hpp */
#ifndef LINFERENCE_HPP
#define LINFERENCE_HPP

#include <QObject>
#include "lkb.hpp"

class LInference : public QObject
{
    Q_OBJECT

    static LNode* isa(LNode* node);
    static LNode* situation(LNode* node);
    static LNode* peekDesc(LNode* node, QList<LNode*> forbidden);

public:
    explicit LInference(QObject *parent = 0);

    static QString generate(LNode* selectedTemplate, QList<LNode*> selectedEntities);

signals:

public slots:

};

#endif // LINFERENCE_HPP
/* End of file: linference.hpp */
