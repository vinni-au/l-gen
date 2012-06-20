#ifndef TEMPLATEPAGE_HPP
#define TEMPLATEPAGE_HPP

#include <QWizardPage>

namespace Ui {
class TemplatePage;
}

class TemplatePage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit TemplatePage(QWidget *parent = 0);
    ~TemplatePage();
    
private:
    Ui::TemplatePage *ui;
};

#endif // TEMPLATEPAGE_HPP
