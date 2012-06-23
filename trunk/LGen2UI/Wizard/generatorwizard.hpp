#ifndef GENERATORWIZARD_HPP
#define GENERATORWIZARD_HPP

#include <QWizard>
#include "LGen2Core/lontology.hpp"

namespace Ui {
class GeneratorWizard;
}

class GeneratorWizard : public QWizard
{
    Q_OBJECT
    
public:
    GeneratorWizard(LOntology* templateOntology, LOntology* domainOntology, QWidget *parent = 0);
    ~GeneratorWizard();
    
private:
    Ui::GeneratorWizard *ui;

    LOntology* m_domainOnlotogy;
    LOntology* m_templateOntology;
};

#endif // GENERATORWIZARD_HPP
