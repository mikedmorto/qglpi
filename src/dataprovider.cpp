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

void DataProvider::setLogin(const LoginItem &login)
{
    this->currentLogin = login;
    this->client.setLogin(this->currentLogin);
}

LoginItem DataProvider::getLogin() const
{
    return this->currentLogin;
}

void DataProvider::setIgnoreSslCert(bool isIgnoreSsl)
{
    this->isIgnoreSsl = isIgnoreSsl;
    this->client.setIgnoreSslCert(this->isIgnoreSsl);
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
    isError = false;
    client.logout();
    loop.exec();

    if (isError){
        isError = false;
        return false;
    }
    result = client.getResult();

    return true;
}

bool DataProvider::getMyProfiles()
{
    isError = false;
    client.getMyProfiles();
    loop.exec();

    if (isError){
        isError = false;
        return false;
    }
    result = client.getResult();

    return true;
}

bool DataProvider::getFullSession()
{
    isError = false;
    client.getFullSession();
    loop.exec();

    if (isError){
        isError = false;
        return false;
    }
    result = client.getResult();

    return true;
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
