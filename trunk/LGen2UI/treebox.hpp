#ifndef TREEBOX_HPP
#define TREEBOX_HPP

#include <QComboBox>
#include <QDirModel>
#include <QTreeView>
#include <QEvent>
#include <QMouseEvent>
#include <QModelIndex>

class TreeBox : public QComboBox
{
    Q_OBJECT
public:
    TreeBox(QWidget* parent = 0);

    bool eventFilter(QObject* object, QEvent* event);

    virtual void showPopup();

    virtual void hidePopup();

private:
    bool skipNextHide;
};

#endif // TREEBOX_HPP
