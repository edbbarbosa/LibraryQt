#include "configwindow.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <iostream>

ConfigWindow::ConfigWindow(QWidget *parent) : QDialog(parent, Qt::Tool)
{
    // Create VBox
    QVBoxLayout *vbox = new QVBoxLayout;

    // Create HBox
    QHBoxLayout *hbox = new QHBoxLayout;

    setLayout(vbox);

    // Create form
    QFormLayout *form = new QFormLayout;

    // Create form entries
    QLineEdit *hostnameEdit = new QLineEdit;
    QLineEdit *databaseEdit = new QLineEdit;
    QLineEdit *usernameEdit = new QLineEdit;
    QLineEdit *passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);

    // Add entries to form
    form->addRow("Hostname:", hostnameEdit);
    form->addRow("Database:", databaseEdit);
    form->addRow("Username:", usernameEdit);
    form->addRow("Password:", passwordEdit);

    // Create OK button
    QPushButton *okBtn = new QPushButton("OK");

    // Create cancel button
    QPushButton *cancelBtn = new QPushButton("Cancel");

    // Add from to vox
    vbox->addLayout(form);

    // Add hbox to vbox
    vbox->addLayout(hbox);

    // Add cancel button to hbox
    hbox->addWidget(cancelBtn);

    // Add ok button to hbox
    hbox->addWidget(okBtn);

    readJson(hostnameEdit, databaseEdit, usernameEdit, passwordEdit);

    connect(okBtn, &QPushButton::clicked, this, [=]() {
        okBtnClicked(hostnameEdit, databaseEdit, usernameEdit, passwordEdit);
    });
    connect(cancelBtn, &QPushButton::clicked, this, &ConfigWindow::close);
}

void ConfigWindow::readJson(QLineEdit *hostnameEdit, QLineEdit *databaseEdit, QLineEdit *usernameEdit, QLineEdit *passwordEdit) {

    Config *config = new Config;

    if(config->readJson()){
        hostnameEdit->setText(config->getHostname());
        databaseEdit->setText(config->getDatabase());
        usernameEdit->setText(config->getUsername());
        passwordEdit->setText(config->getPassword());
    } else {
        std::cerr << "Error" << std::endl;
    }

}

void ConfigWindow::okBtnClicked(QLineEdit *hostnameEdit, QLineEdit *databaseEdit, QLineEdit *usernameEdit, QLineEdit *passwordEdit){
    Config *config = new Config(hostnameEdit->text(), databaseEdit->text(), usernameEdit->text(), passwordEdit->text());

    if(config->saveJson()){
        emit configEdited();
        close();
    } else {
        std::cerr << "Error" << std::endl;
    }
}
