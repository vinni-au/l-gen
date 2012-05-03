/* Begin of file: ledge.hpp */

/*
 * Copyright (C) 2011-2012  Anton Storozhev, antonstorozhev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef LEDGE_HPP
#define LEDGE_HPP

#include <QObject>
#include <QList>

class LNode;

//! Дуга сем.сети (внутреннее представление)
class LEdge : public QObject
{
    Q_OBJECT

public:
    LEdge(QString name, LNode* node = 0, QObject *parent = 0);

    //! Возвращает имя дуги
    /*!
      \sa m_name
    */
    QString name() const
    {   return m_name;  }

    //! Возвращает указатель на вершину, в которую ведёт дуга
    /*!
      \sa m_node
    */
    LNode* node() const
    {   return m_node;  }

signals:

public slots:

private:
    //! Имя дуги
    /*!
      \sa name()
    */
    QString m_name;

    //! Указатель на вершину, в которую ведёт дуга
    /*!
      \sa node()
    */
    LNode* m_node;
};

#include "lnode.hpp"

#endif // LEDGE_HPP
/* End of file: ledge.hpp */
