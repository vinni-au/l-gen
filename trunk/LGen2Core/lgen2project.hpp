/* Begin of file: lgen2project.hpp */

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

#ifndef LGEN2PROJECT_HPP
#define LGEN2PROJECT_HPP

#include <QObject>
#include <QFile>
#include "LGen2Core/lkb.hpp"
#include "LGen2Core/lontologymanager.hpp"

//! Проект L-Gen 2
// TODO: add multiple ontologies support
class LGen2Project : public QObject
{
    Q_OBJECT
public:
    LGen2Project(QString name, QFile* file, QObject *parent = 0);
    ~LGen2Project();

    //! Задаёт файл с онтологией шаблонов задач
    /*!
      \param file файл
      \sa m_templateOntologyFile
    */
    bool setTemplateOntologyFromFile(QFile* file);

    //! Задаёт файл с онтологией предметной области
    /*!
      \param file файл
      \sa m_domainOntologyFile
    */
    bool setDomainOntologyFromFile(QFile* file);

    //! Возвращает указатель на базу знаний
    /*!
      \sa m_kb
    */
    LKB* kb() const
    {   return m_kb;    }

    //! Возвращает имя проекта
    /*!
      \sa m_name
     */
    QString name() const
    {   return m_name;    }

    //! Задаёт имя проекта
    void setName(QString name)
    {   m_name = name;  }

    void setFilename(QString filename)
    {   m_file->setFileName(filename);  }
    QString filename() const
    {   return m_file->fileName();  }

    QString tfilename() const
    {   return m_templateOntologyFile->fileName();  }
    QString dfilename() const
    {   return m_domainOntologyFile->fileName();    }

    void createEmptyDomainOntology(QString filename);
    void createEmptyTemplateOntology(QString filename);

    static LGen2Project* load(QString filename);

signals:

public slots:
        void save();

private:
    //! Название проекта
    QString m_name;

    //! Файл проекта
    QFile* m_file;

    //! Файл с онтологией шаблонов задач
    /*!
      \sa setTemplateOntologyFromFile()
    */
    QFile* m_templateOntologyFile;

    //! Файл с онтологией предметной области
    /*!
      \sa setDomainOntologyFromFile()
    */
    QFile* m_domainOntologyFile;

    //! Указатель на базу знаний
    /*!
      \sa kb()
    */
    LKB* m_kb;
};

#endif // LGEN2PROJECT_HPP
/* End of file: lgen2project.hpp */
