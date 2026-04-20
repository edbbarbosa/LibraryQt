#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Library");

    // Create of UI components
    // Create container
    QWidget *containerTable = new QWidget(this);
    // Create VBox
    QVBoxLayout *vbox = new QVBoxLayout(containerTable);
    // Create HBox
    QHBoxLayout *hbox = new QHBoxLayout;
    // Create menu
    QMenuBar *menuBar = new QMenuBar;
    // Create table
    tableView = new QTableView(containerTable);
    // Create delete button
    QPushButton *delBookBtn = new QPushButton("Delete Book");
    // Create add button
    QPushButton *addBookBtn = new QPushButton("Add Book");

    // Connect to database
    // Read json file
    Config *config = new Config;
    if(!config->readJson()){
        configEdit();
    }
    // Connect to database
    db = new Db(config->getHostname(), config->getDatabase(), config->getUsername(), config->getPassword());
    // Get table
    model = db->getTable();


    // Add actions
    // Add actions to menubar
    QMenu *fileMenu = menuBar->addMenu("File");
    QMenu *helpMenu = menuBar->addMenu("Help");
    // Add config action
    QAction *configAction = fileMenu->addAction("Config");
    fileMenu->addAction(configAction);
    // Add quit action
    QAction *quitAction = fileMenu->addAction("Quit");
    fileMenu->addAction(quitAction);
    // Add about action
    QAction *aboutAction = helpMenu->addAction("About");
    helpMenu->addAction(aboutAction);

    // setModel
    tableView->setModel(model);
    // Adjusts in table
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setAlternatingRowColors(true);

    // Structure
    //
    vbox->setMenuBar(menuBar);
    //
    vbox->addWidget(tableView);
    //
    vbox->addLayout(hbox);
    //
    hbox->addWidget(delBookBtn);
    //
    hbox->addWidget(addBookBtn);

    // Define container as central widget
    setCentralWidget(containerTable);

    // Connect buttons and actions
    connect(delBookBtn, &QPushButton::clicked, this, &MainWindow::removeSelectedBook);
    connect(addBookBtn, &QPushButton::clicked, this, &MainWindow::addBook);
    connect(configAction, &QAction::triggered, this, &MainWindow::configEdit);
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::removeSelectedBook() {
    // Get selection model of table
    QItemSelectionModel *selection = tableView->selectionModel();
    // Get selected lines
    QModelIndexList selectionList = selection->selectedRows();

    if (selectionList.isEmpty()) {
        QMessageBox::information(this, "", "Please select a line to delete.");
        return;
    }

    //
    auto ask = QMessageBox::question(this, "Remove Book(s)",
                                          "Are you sure you want to remove the selected book(s)?",
                                          QMessageBox::Yes | QMessageBox::No);

    if (ask == QMessageBox::Yes) {
        // Delete model lines
        for (int i = selectionList.count() - 1; i >= 0; --i) {
            model->removeRow(selectionList.at(i).row());
        }

        // Update table
        model->select();
    }
}

void MainWindow::addBook(){
    AddBook *addBook = new AddBook(nullptr);
    addBook->setAttribute(Qt::WA_DeleteOnClose); // Delete from memory after close
    connect(addBook, &AddBook::bookAdded, this, [this]() {
        model->setTable("books");
        if (!model->select()) {
            qDebug() << "Error:" << model->lastError().text();
        }
    });

    addBook->show();

}

void MainWindow::configEdit(){
    ConfigWindow *configWindow = new ConfigWindow(nullptr);
    configWindow->setAttribute(Qt::WA_DeleteOnClose); // Delete from memory after close
    connect(configWindow, &ConfigWindow::configEdited, this, [this]() {
        model->setTable("books");
        if (!model->select()) {
            qDebug() << "Error:" << model->lastError().text();
        }
    });

    configWindow->show();
}

void MainWindow::about(){
    QMessageBox::about(this, "About Library",
                       "<h3>Library</h3>"
                       "<a href='https://github.com/edbbarbosa'>@edbbarbosa</a>"
                       "<p>This program is licensed under the GNU GPL v3.0.</p>");
}
