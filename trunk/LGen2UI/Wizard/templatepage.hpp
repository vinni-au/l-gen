#ifndef TEMPLATEPAGE_HPP
#define TEMPLATEPAGE_HPP

#include <QWizardPage>
#include "LGen2Core/lontology.hpp"
#include "LGen2MVC/lontologymodel.hpp"

namespace Ui {
class TemplatePage;
}

class TemplatePage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit TemplatePage(LOntology *templateOntology, QWidget *parent = 0);
    ~TemplatePage();

    LNode* selectedNode() const
    {   return m_selectedNode;  }

protected:
    bool validatePage();
    
private:
    Ui::TemplatePage *ui;

    LOntology* m_ontology;
    LOntologyModel* m_model;

    LNode* m_selectedNode;
};

#endif // TEMPLATEPAGE_HPP
