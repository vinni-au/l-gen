#ifndef CATEGORIZER_HPP
#define CATEGORIZER_HPP

#include <QObject>
#include <QLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHash>

class Category;
class Element;
class Section;
class Button;

class Section : public QObject
{
    Q_OBJECT

public:
    Section(QString caption) : m_caption(caption) {}

    QList< Category* > categories() const
    {   return m_categories;    }

private:
    QString m_caption;
    QList< Category* > m_categories;

    QWidget* m_tab;

    friend class Categorizer;
};

class Category : public QObject
{
    Q_OBJECT

public:
    Category(QString caption, Section* section) :
        m_caption(caption), m_section(section) {}

    Section* section() const
    {   return m_section;   }

    QList< Element* > elements() const
    {   return m_elements;  }

private:
    QString m_caption;
    Section* m_section;
    QList< Element* > m_elements;

    QFrame* m_frame;
    QLabel* m_label;

    friend class Categorizer;
};

class Element : public QObject
{
    Q_OBJECT

public:
    Element(QString name, Category* category, bool link) :
        m_name(name), m_category(category), m_link(link) {}

    Category* category() const
    {   return m_category;  }

    Button* button() const
    {   return m_button;    }

    bool isLink() const
    {   return m_link;  }

private:
    QString m_name;
    Category* m_category;

    Button* m_button;

    bool m_link;

    friend class Categorizer;
};

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(QString text, Element* element);

    void afterAllCreated();

signals:
    void activated(Element* element);
    void deactivated(Element* element);

private slots:
    void onClick(bool checked);
    void onToggle(bool toggled);

private:
    Element* m_element;

    QList< Button* > m_others;
};

class Categorizer : public QObject
{
    Q_OBJECT
public:
    explicit Categorizer(QObject *parent = 0);

    void applyToTabWidget(QTabWidget* widget);

    bool addSection(QString name);
    bool addCategoryToSection(QString category, QString section);
    bool addElementToCategory(QString element, QString category, bool link = true);

signals:
    void node(QString name);
    void startLink(QString name);
    void endLink();

private slots:
    void elementActivated(Element* elem);
    void elementDeactivated(Element* elem);
    
private:
    QHash< QString, Section* >   m_sections;
    QHash< QString, Category* >  m_categories;
    QHash< QString, Element* >   m_elements;
};


#endif // CATEGORIZER_HPP
