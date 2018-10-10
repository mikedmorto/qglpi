#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QTemporaryDir>
#include <QStandardPaths>
#include "mlog.h"
#include "def.h"

class Config
{
    enum Language{
        Lang_en = 0
        ,Lang_ru
    };

    QString lang;
    int loglevel;
    QString logfile;

public:
    explicit Config();
    void load();
    void save();

    void setLang(int lang);
    void setLoglevel(int level);
    void setLogfile(const QString &path);

    int getLang()const;
    QString getLangString()const;
    int getLoglevel()const;
    QString getLogfile()const;
};

#endif // CONFIG_H
