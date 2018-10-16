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

    if (isError){
        isError = false;
        return false;
    }
    result = client.getResult();

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
