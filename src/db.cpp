#include "db.h"
#include <QMessageBox>

Db::Db(QString hostname, QString database, QString username, QString password, QObject *parent) : QObject(parent) {

    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        db = QSqlDatabase::database(QSqlDatabase::defaultConnection);
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(hostname);
        db.setDatabaseName(database);
        db.setUserName(username);
        db.setPassword(password);
    }

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Connection Error",
                              "Unable to connect to MySQL: " + db.lastError().text());
        return;
    }
}

Db::~Db(){

    /*

    if(model){
        delete model;
        model = nullptr;
    }

    if (db.isOpen()){
        db.close();
    }

    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

*/
}

QSqlTableModel* Db::getTable(){
    if(model){
        delete model;
    }

    model = new QSqlTableModel(this, db);
    model->setTable("books"); // Table name in MySQL
    if(!model->select()){
        qDebug() << "Select error" << model->lastError().text();
    }
    if (model->lastError().isValid()) {
        qDebug() << "Model error" << model->lastError().text();
    }
    qDebug() << "Number of lines:" << model->rowCount();

    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    return model;
}

bool Db::addBook(const QString isbn, const QString title, const QString author, const QString publisher, const QString price, const QString year, const QString edition){
    QSqlQuery query(db);
    query.prepare("INSERT INTO books (isbn, title, author, publisher, price, year, edition) VALUES (:isbn, :title, :author, :publisher, :price, :year, :edition)");
    query.bindValue(":isbn", isbn);
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":publisher", publisher);
    query.bindValue(":price", price);
    query.bindValue(":year", year);
    query.bindValue(":edition", edition);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        QSqlDatabase::removeDatabase("books_conn");
        return false;
    }
    return true;
}

bool Db::isOpen(){
    if (!db.open())
        return false;
     return true;
}
