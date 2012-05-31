#ifndef LGEN2EDITOR_HPP
#define LGEN2EDITOR_HPP

#include <QWidget>
#include "LGen2MVC/lontologymodel.hpp"

namespace Ui {
    class LGen2Editor;
}

class LGen2Editor : public QWidget
{
    Q_OBJECT

public:
    explicit LGen2Editor(QWidget *parent = 0);
    ~LGen2Editor();

    void loadModels(LOntologyModel* templateModel, LOntologyModel* domainModel);
    void unloadModels();

private slots:
    void addNodeToDO(QString name);
    void addNodeToTO(QString name);

    void linkModeOnDO(QString name);
    void linkModeOnTO(QString name);

    void linkModeOffDO();
    void linkModeOffTO();

private:
    Ui::LGen2Editor *ui;
};

#endif // LGEN2EDITOR_HPP
