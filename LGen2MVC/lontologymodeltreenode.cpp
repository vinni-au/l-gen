/* Begin of file: lontologymodeltreenode.сpp */
#include "lontologymodeltreenode.hpp"

LOntologyModelTreeNode::LOntologyModelTreeNode(LNode *node, Type type, QObject *parent) :
    QObject(parent), m_node(node), m_parent(0), m_checked(false)
{   }

bool LOntologyModelTreeNode::checked() const
{
    return m_checked;
}

/* End of file: lontologymodeltreenode.сpp */
