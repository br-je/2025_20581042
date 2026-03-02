#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);

    connect(ui->pushButton, &QPushButton::released,
            this, &MainWindow::handleButton1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton1()
{
    emit statusUpdateMessage("Button 1 clicked", 3000);
}
