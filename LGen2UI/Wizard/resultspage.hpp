#ifndef RESULTSPAGE_HPP
#define RESULTSPAGE_HPP

#include <QWizardPage>

namespace Ui {
class ResultsPage;
}

class ResultsPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit ResultsPage(QWidget *parent = 0);
    ~ResultsPage();
    
private:
    Ui::ResultsPage *ui;
};

#endif // RESULTSPAGE_HPP
