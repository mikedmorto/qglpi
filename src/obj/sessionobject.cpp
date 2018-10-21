#include "sessionobject.h"

using namespace GLP;

SessionObject::SessionObject()
{
    type = Type_SessionObject;
}

QJsonObject SessionObject::toJsonObject() const
{
    QJsonObject object;
    QJsonObject sobj;
    sobj["glpiname"]            = this->sessionGLPI.glpiname;
    sobj["glpirealname"]        = this->sessionGLPI.glpirealname;
    sobj["glpifirstname"]       = this->sessionGLPI.glpifirstname;
    sobj["glpi_currenttime"]    = this->sessionGLPI.glpi_currenttime.toString(FORMAT_DATETIME);


    object.insert("session",sobj);
    qDebug()<<object;
    return object;
}

void SessionObject::fromJsonObject(const QJsonObject &object)
{
    this->sessionGLPI.clear();
    QJsonObject sobj = object["session"].toObject();
    this->sessionGLPI.glpiname = sobj["glpiname"].toString();
    this->sessionGLPI.glpirealname = sobj["glpirealname"].toString();
    this->sessionGLPI.glpifirstname = sobj["glpifirstname"].toString();
    this->sessionGLPI.glpi_currenttime = QDateTime::fromString( sobj["glpi_currenttime"].toString(),FORMAT_DATETIME);
}
