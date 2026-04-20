#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include "db.h"
#include "config.h"

class AddBook : public QWidget
{
    Q_OBJECT
    QLineEdit *isbnEdit;
    QLineEdit *titleEdit;
    QLineEdit *authorEdit;
    QLineEdit *publisherEdit;
    QLineEdit *priceEdit;
    QLineEdit *yearEdit;
    QLineEdit *editionEdit;
    void okBtnClicked();
    Db *db = nullptr;
public:
    AddBook(QWidget *parent = nullptr);
signals:
    void bookAdded();
};

#endif // ADDBOOK_H
