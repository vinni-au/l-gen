/* Begin of file: resultwidget.hpp */
#ifndef RESULTWIDGET_HPP
#define RESULTWIDGET_HPP

#include <QWidget>
#include "./../LGen2Core/linference.hpp"

class MainWindow;

namespace Ui {
    class ResultWidget;
}

class ResultWidget : public QWidget
{
    Q_OBJECT

    MainWindow* m_mainw;

public:
    ResultWidget(MainWindow* mainw, QWidget *parent = 0);
    ~ResultWidget();

private slots:
    void on_btn_generate_clicked();

private:
    Ui::ResultWidget *ui;
};

#include "./../mainwindow.hpp"

#endif // RESULTWIDGET_HPP
/* End of file: resultwidget.hpp */
