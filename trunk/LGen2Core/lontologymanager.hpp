/* Begin of file: lontologymanager.hpp */
#ifndef LONTOLOGYMANAGER_HPP
#define LONTOLOGYMANAGER_HPP

#include <QObject>
#include <QDomDocument>
#include <QFile>
#include <QHash>
#include "lnode.hpp"
#include "lontology.hpp"

class LOntologyManager : public QObject
{
    Q_OBJECT
public:
    explicit LOntologyManager(QObject *parent = 0);

    static LOntology* loadOWLXML(QFile* file);
    bool saveOWLXML(QString filename);

signals:

public slots:

};

#endif // LONTOLOGYMANAGER_HPP
/* End of file: lontologymanager.hpp */
