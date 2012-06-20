#ifndef GENERATORWIZARD_HPP
#define GENERATORWIZARD_HPP

#include <QWizard>

namespace Ui {
class GeneratorWizard;
}

class GeneratorWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit GeneratorWizard(QWidget *parent = 0);
    ~GeneratorWizard();
    
private:
    Ui::GeneratorWizard *ui;
};

#endif // GENERATORWIZARD_HPP
