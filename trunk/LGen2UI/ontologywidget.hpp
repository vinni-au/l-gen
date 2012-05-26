/* Begin of file: ontologywidget.hpp */
#ifndef ONTOLOGYWIDGET_HPP
#define ONTOLOGYWIDGET_HPP

#include <QWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QTextEdit>
#include "LGen2MVC/lontologymodel.hpp"

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

    // TODO: do work with categories more elegantly
    void setCaseFramesVisible(bool visible = true);

private:
    Ui::OntologyWidget *ui;
};

#endif // ONTOLOGYWIDGET_HPP
/* End of file: ontologywidget.hpp */
