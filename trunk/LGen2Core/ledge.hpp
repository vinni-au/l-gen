/* Begin of file: ledge.hpp */
#ifndef LEDGE_HPP
#define LEDGE_HPP

#include <QObject>
#include <QList>

class LNode;

class LEdge : public QObject
{
    Q_OBJECT

    QString m_name;
    LNode* m_node;

public:
    LEdge(QString name, LNode* node = 0, QObject *parent = 0);

    QString name() const
    {   return m_name;  }
    LNode* node() const
    {   return m_node;  }

signals:

public slots:

};

#include "lnode.hpp"

#endif // LEDGE_HPP
/* End of file: ledge.hpp */
