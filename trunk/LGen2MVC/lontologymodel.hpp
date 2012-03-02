/* Begin of file: lontologymodel.hpp */
#ifndef LONTOLOGYMODEL_HPP
#define LONTOLOGYMODEL_HPP

#include <QAbstractItemModel>
#include "LGen2Core/lontology.hpp"
#include "lontologymodeltreenode.hpp"

class LOntologyModel : public QAbstractItemModel
{
    Q_OBJECT

    LOntology* m_ontology;
    LOntologyModelTreeNode* m_rootNode;
    bool m_checkOnlyLeaves;
    QList<LNode*> m_checkedNodes;

    LOntologyModelTreeNode* nodeFromIndex(const QModelIndex& index) const;

public:
    explicit LOntologyModel(QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;

    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    LOntology* ontology() const
    {   return m_ontology;  }
    void setOntology(LOntology* ontology);

    void setCheckedOnlyLeaves(bool value)
    {   m_checkOnlyLeaves = value;    }

    QList<LNode*> checkedNodes() const
    {   return m_checkedNodes;  }

    virtual void onNodeChecked(LOntologyModelTreeNode* treeNode);
    virtual void onNodeUnchecked(LOntologyModelTreeNode* treeNode);

signals:
    void nodeChecked(LNode* node);
    void nodeUnchecked(LNode* node);

public slots:

};

#endif // LONTOLOGYMODEL_HPP
/* Begin of file: lontologymodel.hpp */
