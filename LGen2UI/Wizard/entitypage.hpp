#ifndef ENTITYPAGE_HPP
#define ENTITYPAGE_HPP

#include <QWizardPage>
#include "LGen2Core/lontology.hpp"
#include "LGen2MVC/lontologymodel.hpp"

namespace Ui {
class EntityPage;
}

class EntityPage : public QWizardPage
{
    Q_OBJECT
    
public:
    EntityPage(LOntology* domainOntology, QWidget *parent = 0);
    ~EntityPage();

    LNode* selectedNode() const
    {   return m_selectedNode;  }

protected:
    bool validatePage();
    
private:
    Ui::EntityPage *ui;

    LOntology* m_ontology;
    LOntologyModel* m_model;

    LNode* m_selectedNode;
};

#endif // ENTITYPAGE_HPP
