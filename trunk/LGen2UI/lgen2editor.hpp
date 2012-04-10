#ifndef LGEN2EDITOR_HPP
#define LGEN2EDITOR_HPP

#include <QWidget>

namespace Ui {
    class LGen2Editor;
}

class LGen2Editor : public QWidget
{
    Q_OBJECT

public:
    explicit LGen2Editor(QWidget *parent = 0);
    ~LGen2Editor();

private:
    Ui::LGen2Editor *ui;
};

#endif // LGEN2EDITOR_HPP
