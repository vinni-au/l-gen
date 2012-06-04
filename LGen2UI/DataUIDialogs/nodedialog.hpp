#ifndef NODEDIALOG_HPP
#define NODEDIALOG_HPP

#include <QDialog>
#include "LGen2MVC/lontologymodel.hpp"

namespace Ui {
class NodeDialog;
}

class NodeDialog : public QDialog
{
    Q_OBJECT
    
public:
    NodeDialog(QString caption, LOntologyModel* ontologyModel, QString parent = QString(), QString name = QString());
    ~NodeDialog();

private slots:
    void on_btnAdd_clicked();
    void on_btnAddClose_clicked();

private:
    Ui::NodeDialog *ui;

    LOntologyModel* m_model;
};

#endif // NODEDIALOG_HPP
