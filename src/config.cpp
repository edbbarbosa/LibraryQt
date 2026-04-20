#include "config.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <iostream>

Config::Config(QString hostname, QString database, QString username, QString password) {
    this->hostname = hostname;
    this->database = database;
    this->username = username;
    this->password = password;
}

bool Config::readJson(){
    QFile file("config.json");
    if (!file.open(QIODevice::ReadOnly)) return false;

    // 1. Ler os dados brutos do arquivo
    QByteArray configBytes = file.readAll();

    // 2. Converter para documento JSON
    QJsonDocument doc = QJsonDocument::fromJson(configBytes);

    // 3. Acessar os campos (verificando se é objeto)
    if (doc.isObject()){

        QJsonObject json = doc.object();
        hostname = json["hostname"].toString();
        database = json["database"].toString();
        username = json["username"].toString();
        password = json["password"].toString();
        return true;
    } else {
        std::cerr << "Error" << std::endl;
        return false;
    }
}

bool Config::saveJson(){
    QJsonObject json;
    json["hostname"] = hostname;
    json["database"] = database;
    json["username"] = username;
    json["password"] = password; // Arrays

    // 2. Criar o documento
    QJsonDocument doc(json);

    // 3. Salvar no arquivo
    QFile file("config.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson()); // Use doc.toJson(QJsonDocument::Indented) para ficar legível
        file.close();
        qDebug() << "JSON salvo com sucesso!";
        return true;
    }
    return false;
}

QString Config::getHostname(){
    return hostname;
}

QString Config::getDatabase(){
    return database;
}

QString Config::getUsername(){
    return username;
}

QString Config::getPassword(){
    return password;
}
