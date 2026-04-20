#include "addbook.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QIntValidator>
#include <QMessageBox>
#include <QDoubleValidator>
#include <iostream>

AddBook::AddBook(QWidget *parent):
    QWidget(parent)
{

    Config *config = new Config;
    if(config->readJson()){
        // Connect to database
        db = new Db(config->getHostname(), config->getDatabase(), config->getUsername(), config->getPassword());
    }

    // Create VBox
    QVBoxLayout *vbox = new QVBoxLayout;
    // Create HBox
    QHBoxLayout *hbox = new QHBoxLayout;

    setLayout(vbox);

    // Create form
    QFormLayout *form = new QFormLayout;

    // Create form entries
    isbnEdit = new QLineEdit;
    QRegularExpression re("^[0-9]+$");
    QRegularExpressionValidator *validator0 = new QRegularExpressionValidator(re, isbnEdit);
    isbnEdit->setValidator(validator0);
    isbnEdit->setMaxLength(13);
    titleEdit = new QLineEdit;
    authorEdit = new QLineEdit;
    publisherEdit = new QLineEdit;
    priceEdit = new QLineEdit;
    QDoubleValidator *validator1 = new QDoubleValidator(0.0, 10000.0, 2, this);
    validator1->setNotation(QDoubleValidator::StandardNotation);
    priceEdit->setValidator(validator1); 
    yearEdit = new QLineEdit;
    editionEdit = new QLineEdit;

    // Add entries to form
    form->addRow("ISBN-13:", isbnEdit);
    form->addRow("Title:", titleEdit);
    form->addRow("Author:", authorEdit);
    form->addRow("Publisher:", publisherEdit);
    form->addRow("Price:", priceEdit);
    form->addRow("Year:", yearEdit);
    form->addRow("Edition:", editionEdit);

    // Create OK button
    QPushButton *okBtn = new QPushButton("OK");

    // Create cancel button
    QPushButton *cancelBtn = new QPushButton("Cancel");

    // Add form to vbox
    vbox->addLayout(form);

    // Add hbox to vbox
    vbox->addLayout(hbox);

    // Add cancel button to Hbox
    hbox->addWidget(cancelBtn);

    // Add OK button to HBox
    hbox->addWidget(okBtn);

    connect(okBtn, &QPushButton::clicked, this, &AddBook::okBtnClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &AddBook::close);
}

void AddBook::okBtnClicked(){
    const QString isbn = isbnEdit->text();
    const QString title = titleEdit->text();
    const QString author = authorEdit->text();
    const QString publisher = publisherEdit->text();
    const QString price = priceEdit->text();
    const QString year = yearEdit->text();
    const QString edition = editionEdit->text();

    if(db->addBook(isbn, title, author, publisher, price, year, edition)){
        std::cout << "O título é: " << title.toStdString() << std::endl;
        emit bookAdded();
        close();
        std::cout << "LIVRO INSERIDO COM SUCESSO\n";
    }

}
