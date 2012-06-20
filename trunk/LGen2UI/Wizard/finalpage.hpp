#ifndef FINALPAGE_HPP
#define FINALPAGE_HPP

#include <QWizardPage>

namespace Ui {
class FinalPage;
}

class FinalPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit FinalPage(QWidget *parent = 0);
    ~FinalPage();
    
private:
    Ui::FinalPage *ui;
};

#endif // FINALPAGE_HPP
