#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->treeView, &QTreeView::clicked,
            this, &MainWindow::handleTreeClicked);

    // Create the model
    this->partList = new ModelPartList("Parts List");

    // Attach model to tree view
    ui->treeView->setModel(this->partList);

    // Get root item
    ModelPart* rootItem = this->partList->getRootItem();

    // Add demo data
    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        ModelPart* childItem = new ModelPart({name, visible});
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++) {
            QString subName = QString("Item %1,%2").arg(i).arg(j);
            ModelPart* subItem = new ModelPart({subName, visible});
            childItem->appendChild(subItem);
        }
    }

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

void MainWindow::handleTreeClicked(const QModelIndex &index)
{
    // Get pointer to the underlying ModelPart
    ModelPart* selectedPart =
        static_cast<ModelPart*>(index.internalPointer());

    if (!selectedPart)
        return;

    // Column 0 = name
    QString name = selectedPart->data(0).toString();

    emit statusUpdateMessage("Selected item: " + name, 0);
}

void MainWindow::on_actionOpen_File_triggered()
{
    emit statusUpdateMessage("Open File action triggered", 3000);

    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
        );

    if (fileName.isEmpty())
        return;

    QFileInfo info(fileName);
    emit statusUpdateMessage("Selected file: " + info.fileName(), 3000);

}

