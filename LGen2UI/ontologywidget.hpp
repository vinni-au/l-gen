/* Begin of file: ontologywidget.hpp */
#ifndef ONTOLOGYWIDGET_HPP
#define ONTOLOGYWIDGET_HPP

#include <QWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QTextEdit>
#include "LGen2MVC/lontologymodel.hpp"
#include "categorizer.hpp"

namespace Ui {
    class OntologyWidget;
}

class OntologyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OntologyWidget(QWidget *parent = 0);
    ~OntologyWidget();

    void setModel(LOntologyModel* model);

    void setCategorizer(Categorizer* categorizer);

private:
    Ui::OntologyWidget *ui;

    Categorizer* m_categorizer;
};

#endif // ONTOLOGYWIDGET_HPP
/* End of file: ontologywidget.hpp */
