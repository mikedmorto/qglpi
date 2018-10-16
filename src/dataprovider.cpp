#include "dataprovider.h"

DataProvider::DataProvider(QObject *parent) : QObject(parent)
{
    connect(&client, &RestApiClient::sigFinished, &loop, &QEventLoop::quit);
    connect(&client, &RestApiClient::criticalError, &loop, &QEventLoop::quit);
    connect(&client, &RestApiClient::log, this, &DataProvider::log);
    connect(&client, &RestApiClient::criticalError, this, &DataProvider::slotError);
    connect(&client, &RestApiClient::sigProgress, this, &DataProvider::sigProgress);
    isError = false;
}

QString DataProvider::getLastError()
{
    return lastError;
}

QString DataProvider::getResult()
{
    return result;
}

bool DataProvider::auth(const LoginItem &item)
{
    isError = false;
    this->loginItem = item;
    client.auth(this->loginItem);
    loop.exec();

    // error processing 1
    if (isError){
        isError = false;
        return false;
    }
    result = client.getResult();
    QJsonObject object = QJsonDocument::fromJson(result.toUtf8()).object();
    // error processing 2
    if (object["status"].toString() == "error"){
        lastError = object["message"].toString();
        isError = false;
        return false;
    }

    // error processing 3
    if (object["ssid"].toString().isEmpty()){
        lastError = tr("SSID is empty");
        isError = false;
        return false;
    }

    // well done
    return true;
}

bool DataProvider::logout()
{
    return false;
}

void DataProvider::slotError(const QString &message)
{
    isError = true;
    lastError = message;
}

void DataProvider::slotCancel()
{
    client.slotCancel();
}
