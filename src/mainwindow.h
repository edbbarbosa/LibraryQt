#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSqlTableModel>
#include "addbook.h"
#include "db.h"
#include "configwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void removeSelectedBook();
    void addBook();
    void editarLivro();
    void configEdit();
    void about();

private:
    Ui::MainWindow *ui;
    Db *db = nullptr;
    // Criar a Tabela (View)
    QTableView *tableView = nullptr;
    // --- 3. CONFIGURAÇÃO DO MODELO (DADOS) ---
    QSqlTableModel *model = nullptr;
};
#endif // MAINWINDOW_H
