/* Begin of file: ledge.cpp */
#include "ledge.hpp"

LEdge::LEdge(QString name, LNode *node, QObject *parent) :
    QObject(parent), m_name(name), m_node(node)
{   }

/* End of file: ledge.cpp */
