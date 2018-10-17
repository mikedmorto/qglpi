#include "config.h"

Config::Config()
{
    this->lang = "en";
    this->loglevel = MLog::logAlert;
}

void Config::load()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, CORP_NAME, APP_NAME);
    this->lang = settings.value("lang", "en").toString();
    this->loglevel = settings.value("log_level", MLog::logNone).toInt();
    this->logfile = settings.value("log_file", "").toString();
    int size = settings.beginReadArray("accounts");
    this->logins.clear();
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        LoginItem login;
        login.imp(settings.value("account").toString());
        logins.append(login);
    }
     settings.endArray();

}

void Config::save()
{

    qDebug()<<"logins size is - "<<logins.size();
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, CORP_NAME, APP_NAME);
    settings.setValue("lang", this->lang);
    settings.setValue("log_level", this->loglevel);
    settings.setValue("log_file", this->logfile);
    settings.beginWriteArray("accounts");
    for (int i = 0; i < logins.size(); ++i) {
    settings.setArrayIndex(i);
    settings.setValue("account", this->logins[i].exp());
    }
    settings.endArray();
}

void Config::setLang(int lang)
{
    switch (lang){
        case Lang_ru:
            this->lang = "ru";
            break;
        case Lang_en:
        default:
            this->lang = "en";
            break;
    }
}

void Config::setLoglevel(int level)
{
    this->loglevel = level;
}

void Config::setLogfile(const QString &path)
{
    this->logfile = path;
}

void Config::setLogins(const QVector<LoginItem> &vec)
{
    this->logins = vec;
}


int Config::getLang() const
{
    if (this->lang == "en")
       return Lang_en;
    if (this->lang == "ru")
       return Lang_ru;
    return Lang_en;
}

QString Config::getLangString() const
{
    return this->lang;
}

int Config::getLoglevel() const
{
    return this->loglevel;
}

QString Config::getLogfile() const
{
    return this->logfile;
}

QVector<LoginItem> Config::getLogins() const
{
    return this->logins;
}
