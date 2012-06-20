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

protected:
    void timerEvent(QTimerEvent *);

private slots:
    void on_btnAdd_clicked();
    void on_btnAddClose_clicked();

private:
    Ui::NodeDialog *ui;

    int m_timerId;

    LOntologyModel* m_model;
};

#endif // NODEDIALOG_HPP
