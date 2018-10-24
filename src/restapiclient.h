#ifndef RESTAPICLIENT_H
#define RESTAPICLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include "config.h"
#include "mlog.h"
#include "def.h"
#include "dialogindata.h"

class RestApiClient : public QObject
{
    Q_OBJECT

    QString me = "api";
    QNetworkAccessManager *networkManager;

    enum Stage {
        Null = 0,
        Stage_Auth,
        Stage_Logout,
        Stage_getMyProfiles,
        Stage_getFullSession,
        Stage_getMyEntities,
        Stage_getActiveEntities
    };

    Stage stage;
    LoginItem loginItem;
    QString session_token;
    QJsonDocument json;
    LoginItem currentLogin;
    bool isIgnoreSsl = false;


    void invokeGet(QNetworkRequest &request);

public:
    explicit RestApiClient(QObject *parent = nullptr);
    ~RestApiClient();

    QString getResult()const;
    void setLogin(const LoginItem &login);
    LoginItem getLogin()const;
    void setIgnoreSslCert(bool isIgnoreSsl);

signals:
    void log(const QString &,MLog::LogLevel,const QString &);
    void criticalError(const QString &message);
    void sigFinished();
    // DiaWait control
    void sigSetDiawaitText(const QString &text);
    void sigProgress(const qint64 &bytesNow, const qint64 &bytesTotal);


    void authDone(const QString &data);
    void logoutDone(const QString &data);
    void getMyProfilesDone(const QString &data);
    void getFullSessionDone(const QString &data);
    void getMyEntitiesDone(const QString &data);
public slots:
    void auth(const LoginItem &loginItem);
    void logout();
    void getMyProfiles();
    void getFullSession();
    void getMyEntities();
    void getActiveEntities();


    void replyFinished(QNetworkReply *reply);
    void error(const QString &message);
    void slotCancel();
};

#endif // RESTAPICLIENT_H
