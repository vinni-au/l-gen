#ifndef ONTOLOGYEDITORWINDOW_HPP
#define ONTOLOGYEDITORWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class OntologyEditorWindow;
}

class OntologyEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OntologyEditorWindow(QWidget *parent = 0);
    ~OntologyEditorWindow();

private:
    Ui::OntologyEditorWindow *ui;
};

#endif // ONTOLOGYEDITORWINDOW_HPP
