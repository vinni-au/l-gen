/* Begin of file: lontologymodeltreenode.hpp */
#ifndef LONTOLOGYMODELTREENODE_HPP
#define LONTOLOGYMODELTREENODE_HPP

#include <QObject>
#include <QList>
#include <LGen2Core/lnode.hpp>

class LOntologyModelTreeNode : public QObject
{
    Q_OBJECT

    LNode* m_node;
    LOntologyModelTreeNode* m_parent;
    QList<LOntologyModelTreeNode*> m_children;
    bool m_checked;

public:
    enum Type
    {
        Root = 0,
        Common
    };

    LOntologyModelTreeNode(LNode* node, Type type = Common, QObject *parent = 0);

    LNode* node() const
    {   return m_node;  }

    LOntologyModelTreeNode* parent() const
    {   return m_parent;    }
    void setParent(LOntologyModelTreeNode* node)
    {   m_parent = node;    }

    QList<LOntologyModelTreeNode*> children() const
    {   return m_children;  }
    void addChild(LOntologyModelTreeNode* node)
    {   m_children << node; }

    int childCount() const
    {   return m_children.count();  }

    bool checked() const;
    void setChecked(bool checked)
    {   m_checked = checked;    }

signals:

public slots:

};

#endif // LONTOLOGYMODELTREENODE_HPP
/* Begin of file: lontologymodeltreenode.hpp */
