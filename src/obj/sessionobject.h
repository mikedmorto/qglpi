#ifndef SESSIONOBJECT_H
#define SESSIONOBJECT_H

#include "abstractobject.h"
#include <QDateTime>


namespace GLP {

struct SessionGLPI
{
    QString glpiname;
    QString glpirealname;
    QString glpifirstname;
    QDateTime glpi_currenttime;
    SessionGLPI(){
        this->clear();
    }
    void clear(){
            glpiname = "";
            glpirealname = "";
            glpifirstname = "";
            glpi_currenttime = QDateTime();
    }
};

class SessionObject : AbstractObject
{
public:
    SessionObject();
    QJsonObject toJsonObject()const;
    void fromJsonObject(const QJsonObject &object);

    SessionGLPI sessionGLPI;
};

}
#endif // SESSIONOBJECT_H
