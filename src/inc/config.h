#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QTemporaryDir>
#include <QStandardPaths>
#include "mlog.h"
#include "def.h"
#include "accountmodel.h"

class Config
{
    enum Language{
        Lang_en = 0
        ,Lang_ru
    };

    QString lang;
    int loglevel;
    QString logfile;
    bool ignoreSsl;
    QVector<LoginItem> logins;

public:
    explicit Config();
    void load();
    void save();

    void setLang(int lang);
    void setLoglevel(int level);
    void setLogfile(const QString &path);
    void setIgnoreSsl(bool state);
    void setLogins(const QVector<LoginItem> &vec);

    int getLang()const;
    QString getLangString()const;
    int getLoglevel()const;
    QString getLogfile()const;
    bool getIgnoreSsl()const;
    QVector<LoginItem> getLogins()const;
};

#endif // CONFIG_H
