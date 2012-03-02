/* Begin of file: lgen2project.hpp */
#ifndef LGEN2PROJECT_HPP
#define LGEN2PROJECT_HPP

#include <QObject>
#include <QFile>
#include "LGen2Core/lkb.hpp"
#include "LGen2Core/lontologymanager.hpp"

class LGen2Project : public QObject
{
    Q_OBJECT

    QString m_name;
    QFile* m_file;
    QFile* m_templateOntologyFile;
    QFile* m_domainOntologyFile;

    LKB* m_kb;

public:
    LGen2Project(QString name, QFile* file, QObject *parent = 0);

    bool setTemplateOntologyFromFile(QFile* file);
    bool setDomainOntologyFromFile(QFile* file);

    LKB* kb() const
    {   return m_kb;    }

signals:

public slots:

};

#endif // LGEN2PROJECT_HPP
/* End of file: lgen2project.hpp */
