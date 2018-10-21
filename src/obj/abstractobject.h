#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>
#include <QString>
#include "def.h"

namespace GLP {

enum ObjectType {
    Abstract = 0,
    Type_SessionObject
};

class AbstractObject
{
public:
    explicit AbstractObject();
    virtual QJsonObject toJsonObject()const = 0;
    virtual void fromJsonObject(const QJsonObject &object) = 0;
    QString toString();
    void fromString(const QString &string);
protected:
    ObjectType type;
};

}

#endif // ABSTRACTOBJECT_H
