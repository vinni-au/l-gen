#include "categorizer.hpp"

Categorizer::Categorizer(QObject *parent) :
    QObject(parent)
{   }

bool Categorizer::addSection(QString section_)
{
    if (m_sections.contains(section_))
        return false;

    Section* section = new Section(section_);
    m_sections.insert(section_, section);
    return true;
}

bool Categorizer::addCategoryToSection(QString category_, QString section_)
{
    if (m_categories.contains(category_))
        return false;

    Section* section = m_sections.value(section_, 0);
    if (!section)
        return false;

    Category* category = new Category(category_, section);
    section->m_categories << category;
    m_categories.insert(category_, category);
    return true;
}

bool Categorizer::addElementToCategory(QString element_, QString category_, bool link)
{
    if (m_elements.contains(element_))
        return false;

    Category* category = m_categories.value(category_, 0);
    if (!category)
        return false;

    Element* element = new Element(element_, category, link);
    category->m_elements << element;
    m_elements.insert(element_, element);
    return true;
}

void Categorizer::applyToTabWidget(QTabWidget *widget)
{
    if (!widget)
        return;

    for (int i = 0; i < m_sections.count(); ++i) {//создаём табы
        Section* section = m_sections.values().at(i);

        int column = 0;

        QWidget* tab = new QWidget;
        widget->addTab(tab, section->m_caption);
        section->m_tab = tab;
        QGridLayout* layout = new QGridLayout;
        layout->setVerticalSpacing(0);
        tab->setLayout(layout);

        for (int j = 0; j < section->m_categories.count(); ++j) {//Создаём группы
            Category* category = section->m_categories.at(j);

            QFrame* frame = new QFrame;
            frame->setLayout(new QHBoxLayout);

            QLabel* label = new QLabel(category->m_caption);
            label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

            category->m_frame = frame;
            category->m_label = label;

            layout->addWidget(frame, 0, column);
            layout->addWidget(label, 1, column++);

            for (int k = 0; k < category->m_elements.count(); ++k) {//Создаём кнопки
                Element* element = category->m_elements.at(k);

                Button* btn = new Button(element->m_name, element);
                btn->setCheckable(element->m_link);
                frame->layout()->addWidget(btn);                

                element->m_button = btn;

                QObject::connect(btn, SIGNAL(activated(Element*)),
                                 SLOT(elementActivated(Element*)));
                QObject::connect(btn, SIGNAL(deactivated(Element*)),
                                 SLOT(elementDeactivated(Element*)));
            }
        }

        layout->addItem(new QSpacerItem(32, 32, QSizePolicy::Expanding), 0, layout->columnCount(), 2);
    }

    QList< Element* > elems = m_elements.values();
    for (int i = 0; i < elems.count(); ++i)
        elems.at(i)->button()->afterAllCreated();
}

void Categorizer::elementActivated(Element *elem)
{
    if (elem->isLink())
        emit startLink(elem->m_name);
    else emit node(elem->m_name);
}

void Categorizer::elementDeactivated(Element *elem)
{
    if (elem->isLink())
        emit endLink();
}

Button::Button(QString text, Element* element) :
    QPushButton(text), m_element(element)
{
    QObject::connect(this, SIGNAL(clicked(bool)),
                     SLOT(onClick(bool)));
    QObject::connect(this, SIGNAL(toggled(bool)),
                     SLOT(onToggle(bool)));
}

void Button::afterAllCreated()
{
    if (isCheckable()) {
        Section* section = m_element->category()->section();

        for (int i = 0; i < section->categories().count(); ++i) {
            Category* category = section->categories().at(i);
            for (int j = 0; j < category->elements().count(); ++j)
                m_others << category->elements().at(j)->button();
        }
        m_others.removeAll(this);
    }
}

void Button::onClick(bool checked)
{
    if (!checked && isCheckable()) {
        emit deactivated(m_element);
        return;
    }
    emit activated(m_element);
}

void Button::onToggle(bool toggled)
{
    if (toggled)
        for (int i = 0; i < m_others.count(); ++i) {
            Button* other = m_others.at(i);
            if (other)
                other->setChecked(false);
        }
}
