#ifndef LEMMATIZERFORM_HPP
#define LEMMATIZERFORM_HPP

#include <QWidget>

namespace Ui {
class LemmatizerForm;
}

class LemmatizerForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit LemmatizerForm(QWidget *parent = 0);
    ~LemmatizerForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LemmatizerForm *ui;

};

#endif // LEMMATIZERFORM_HPP
