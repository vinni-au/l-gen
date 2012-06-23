#ifndef SENTENCEDIALOG_HPP
#define SENTENCEDIALOG_HPP

#include <QDialog>

namespace Ui {
class SentenceDialog;
}

class SentenceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SentenceDialog(QWidget *parent = 0);
    ~SentenceDialog();
    
private:
    Ui::SentenceDialog *ui;
};

#endif // SENTENCEDIALOG_HPP
