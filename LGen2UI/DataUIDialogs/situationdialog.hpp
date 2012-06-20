#ifndef SITUATIONDIALOG_HPP
#define SITUATIONDIALOG_HPP

#include <QDialog>
#include "LGen2MVC/lontologymodel.hpp"

namespace Ui {
class SituationDialog;
}

class SituationDialog : public QDialog
{
    Q_OBJECT
    
public:
    SituationDialog(QString caption, LOntologyModel* model,
                    QString parent = QString("#ситуация"), QString name = QString());
    ~SituationDialog();

protected:
    void timerEvent(QTimerEvent *);
    
private slots:
    void on_btnAdd_clicked();
    void on_btnAddClose_clicked();

private:
    Ui::SituationDialog *ui;

    int m_timerId;

    LOntologyModel* m_model;
};

#endif // SITUATIONDIALOG_HPP
