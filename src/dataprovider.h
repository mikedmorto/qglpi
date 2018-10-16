#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include <QMainWindow>
#include <QEventLoop>
#include <QDateTime>
#include "restapiclient.h"
#include "mlog.h"
#include "dialogindata.h"

class DataProvider : public QObject
{
    Q_OBJECT

    bool checkRequestState();
    RestApiClient client;
    QEventLoop loop;
    LoginItem loginItem;
    QString lastError;
    QString result;
    bool isError;


public:
    explicit DataProvider(QObject *parent = nullptr);

    QString getLastError();
    QString getResult();

    bool auth(const LoginItem &item);
    bool logout();


signals:
    void log(const QString & owner,MLog::LogLevel level,const QString & text);
    void sigProgress(const qint64 &bytesNow, const qint64 &bytesTotal);
private slots:
    void slotError(const QString &message);
public slots:
    void slotCancel();
};

#endif // DATAPROVIDER_H
