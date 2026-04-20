#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include "config.h"
#include <QDialog>
#include <QLineEdit>

class ConfigWindow : public QDialog
{
    Q_OBJECT
    void okBtnClicked(QLineEdit *hostnameEdit, QLineEdit *databaseEdit, QLineEdit *usernameEdit, QLineEdit *passwordEdit);
    void readJson(QLineEdit *hostnameEdit, QLineEdit *databaseEdit, QLineEdit *usernameEdit, QLineEdit *passwordEdit);
public:
    ConfigWindow(QWidget *parent);
signals:
    void configEdited();
};

#endif // CONFIGWINDOW_H
