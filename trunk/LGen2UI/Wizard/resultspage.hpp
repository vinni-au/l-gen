#ifndef RESULTSPAGE_HPP
#define RESULTSPAGE_HPP

#include <QWizardPage>
#include "templatepage.hpp"
#include "entitypage.hpp"

namespace Ui {
class ResultsPage;
}

class ResultsPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit ResultsPage(TemplatePage* tp, EntityPage* ep, QWidget *parent = 0);
    ~ResultsPage();

protected:
    void initializePage();
    
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ResultsPage *ui;

    TemplatePage* m_templatePage;
    EntityPage* m_entityPage;
};

#endif // RESULTSPAGE_HPP
