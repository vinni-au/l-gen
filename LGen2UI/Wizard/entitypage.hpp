#ifndef ENTITYPAGE_HPP
#define ENTITYPAGE_HPP

#include <QWizardPage>

namespace Ui {
class EntityPage;
}

class EntityPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit EntityPage(QWidget *parent = 0);
    ~EntityPage();
    
private:
    Ui::EntityPage *ui;
};

#endif // ENTITYPAGE_HPP
