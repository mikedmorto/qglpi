#include "restapiclient.h"

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

void RestApiClient::auth(const LoginItem &loginItem)
{
    stage = Stage_Auth;

    this->loginItem = loginItem;



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


    QSslConfiguration conf(request.sslConfiguration());
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);
    networkManager->get(request);

//    log(me, MLog::logDebug, QString("Authorization ")
//                .arg(login).arg(pass));

//    QJsonObject object;
//    object["login"] = login;
//    object["password"] = pass;
//    object["apiver"] = API_VER;
//    QJsonDocument document(object);
//    sigPutLog(me, MLog::logDebug, QString(document.toJson()));
//    invokePost("auth", document);

}

void RestApiClient::logout()
{

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
        authDone(json.toJson());
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
