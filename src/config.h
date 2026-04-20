#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class Config
{
    QString hostname, database, username, password;
public:
    Config(QString hostname, QString database, QString username, QString password);
    Config(){};
    bool readJson();
    bool saveJson();
    QString getHostname();
    QString getDatabase();
    QString getUsername();
    QString getPassword();
};

#endif // CONFIG_H
