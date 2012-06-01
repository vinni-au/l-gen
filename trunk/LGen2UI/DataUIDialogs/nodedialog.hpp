#ifndef NODEDIALOG_HPP
#define NODEDIALOG_HPP

#include <QDialog>

namespace Ui {
class NodeDialog;
}

class NodeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NodeDialog(QWidget *parent = 0);
    ~NodeDialog();
    
private:
    Ui::NodeDialog *ui;
};

#endif // NODEDIALOG_HPP
