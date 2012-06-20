#ifndef STARTPAGE_HPP
#define STARTPAGE_HPP

#include <QWizardPage>

namespace Ui {
class StartPage;
}

class StartPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit StartPage(QWidget *parent = 0);
    ~StartPage();
    
private:
    Ui::StartPage *ui;
};

#endif // STARTPAGE_HPP
