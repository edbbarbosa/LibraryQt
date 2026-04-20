#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>

class Db : public QObject
{
    Q_OBJECT
    QSqlDatabase db;
    QSqlTableModel *model = nullptr;
public:
    explicit Db(QString hostname, QString database, QString username, QString password, QObject *parent = nullptr);
    ~Db();
    QSqlTableModel* getTable();
    bool addBook(const QString, const QString, const QString, const QString, const QString, const QString, const QString);
    bool isOpen();
};

#endif // DB_H
