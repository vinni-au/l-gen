/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This file is a part of L-Gen 2.0
 *
 * L-Gen 2.0 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * L-Gen 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
    Element(QString name, Category* category, bool link, QIcon* icon = 0) :
        m_name(name), m_category(category), m_link(link), m_icon(icon) {}

    Category* category() const
    {   return m_category;  }

    Button* button() const
    {   return m_button;    }

    QIcon* icon() const
    {   return m_icon;  }

    bool isLink() const
    {   return m_link;  }

private:
    QString m_name;
    Category* m_category;

    Button* m_button;
    QIcon* m_icon;

    bool m_link;

    friend class Categorizer;
};

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(QString text, Element* element, QIcon* icon = 0);

    void afterAllCreated();

signals:
    void activated(Element* element);
    void deactivated(Element* element);

private slots:
    void onClick(bool checked);

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
    bool addElementToCategory(QString element, QString category, bool link = true, QIcon* icon = 0);

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
