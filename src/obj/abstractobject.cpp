#include "abstractobject.h"

using namespace GLP;

AbstractObject::AbstractObject()
{
    type = Abstract;
}

QString AbstractObject::toString()
{
    QJsonDocument document;
    document.setObject(toJsonObject());
    return QString(document.toJson(QJsonDocument::Indented));
}

void AbstractObject::fromString(const QString &string)
{
    fromJsonObject(QJsonDocument::fromJson(string.toUtf8()).object());
}
