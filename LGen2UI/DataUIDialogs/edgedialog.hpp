#ifndef EDGEDIALOG_HPP
#define EDGEDIALOG_HPP

#include <QDialog>

namespace Ui {
class EdgeDialog;
}

class EdgeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EdgeDialog(QWidget *parent = 0);
    ~EdgeDialog();
    
private:
    Ui::EdgeDialog *ui;
};

#endif // EDGEDIALOG_HPP
