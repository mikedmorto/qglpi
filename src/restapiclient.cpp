#include "restapiclient.h"

void RestApiClient::invokeGet(QNetworkRequest &request)
{
    QSslConfiguration conf(request.sslConfiguration());
    if(isIgnoreSsl){
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    }
    request.setSslConfiguration(conf);
    networkManager->get(request);
}

void RestApiClient::setIgnoreSslCert(bool isIgnoreSsl)
{
    this->isIgnoreSsl = isIgnoreSsl;
    log(me,MLog::logDebug,tr("Set ignore ssl certificates - %1").arg(this->isIgnoreSsl));
}

RestApiClient::RestApiClient(QObject *parent) : QObject(parent)
{
    stage = Null;
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}

RestApiClient::~RestApiClient()
{
    delete networkManager;
}

QString RestApiClient::getResult() const
{
    return json.toJson();
}

void RestApiClient::setLogin(const LoginItem &login)
{
    this->currentLogin = login;
}

LoginItem RestApiClient::getLogin() const
{
    return currentLogin;
}

void RestApiClient::auth(const LoginItem &loginItem)
{
    stage = Stage_Auth;

    this->loginItem = loginItem;

    log(me,MLog::logDebug,tr("Start auth"));

    QNetworkRequest request(QUrl(loginItem.serverurl + "initSession"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    switch (loginItem.authType) {
    case LoginItem::Password:
    default:
        log(me,MLog::logDebug,tr("Auth type password"));
        request.setRawHeader("Authorization",
                          "Basic "+QString(QString("%1:%2")
                                           .arg(loginItem.login)
                                           .arg(loginItem.pass)).toUtf8().toBase64());
        break;
    case LoginItem::Token:
        log(me,MLog::logDebug,tr("Auth type token"));
        request.setRawHeader("Authorization","user_token "+loginItem.token.toUtf8());
        break;
    }

    request.setRawHeader("App-Token", loginItem.apptoken.toUtf8());
    invokeGet(request);
}

void RestApiClient::logout()
{
    stage = Stage_Logout;

    log(me,MLog::logDebug,tr("Start logout"));
    QNetworkRequest request(QUrl(currentLogin.serverurl + "killSession"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Session-Token",currentLogin.session_token.toUtf8());
    request.setRawHeader("App-Token", currentLogin.apptoken.toUtf8());

    invokeGet(request);
}

void RestApiClient::getMyProfiles()
{
    stage = Stage_getMyProfiles;

    log(me,MLog::logDebug,tr("Start getMyProfiles"));
    QNetworkRequest request(QUrl(currentLogin.serverurl + "getMyProfiles"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Session-Token",currentLogin.session_token.toUtf8());
    request.setRawHeader("App-Token", currentLogin.apptoken.toUtf8());

    invokeGet(request);
}

void RestApiClient::getFullSession()
{
    stage = Stage_getFullSession;

    log(me,MLog::logDebug,tr("Start getFullSession"));
    QNetworkRequest request(QUrl(currentLogin.serverurl + "getFullSession"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Session-Token",currentLogin.session_token.toUtf8());
    request.setRawHeader("App-Token", currentLogin.apptoken.toUtf8());

    invokeGet(request);
}

void RestApiClient::replyFinished(QNetworkReply *reply)
{
    log(me, MLog::logDebug, QString("response received"));
    QByteArray data = reply->readAll();
    log(me, MLog::logDebug, QString("respond data = %1").arg(QString(data)));

    if(reply->error() != QNetworkReply::NoError){
        log(me, MLog::logAlert, QString("reply error"));
        error(reply->errorString());
        reply->deleteLater();
        return;
    }
    log(me, MLog::logDebug, QString("reply ok"));
    json = QJsonDocument::fromJson(data);
    QJsonObject object = json.object();

    switch (stage) {
    case Stage_Auth:
        log(me,MLog::logDebug,tr("Done auth"));
        authDone(json.toJson());
        break;
    case Stage_Logout:
        log(me,MLog::logDebug,tr("Done logout"));
        logoutDone(json.toJson());
        break;
    default:
        break;
    }

    sigFinished();
    reply->deleteLater();

}

void RestApiClient::error(const QString &message)
{
    log(me, MLog::logAlert, message);
    switch (stage){
        default:
            criticalError(message);
            break;
    }
}

void RestApiClient::slotCancel()
{
    networkManager->deleteLater();
    error(tr("Rejected"));
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}
