#ifndef SITUATIONDIALOG_HPP
#define SITUATIONDIALOG_HPP

#include <QDialog>

namespace Ui {
class SituationDialog;
}

class SituationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SituationDialog(QWidget *parent = 0);
    ~SituationDialog();
    
private:
    Ui::SituationDialog *ui;
};

#endif // SITUATIONDIALOG_HPP
