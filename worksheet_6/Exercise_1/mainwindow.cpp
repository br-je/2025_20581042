#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include "PartPropertiesDialog.h"

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

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeView, &QTreeView::customContextMenuRequested,
            this, &MainWindow::openContextMenu);

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
    QModelIndex index = ui->treeView->currentIndex();

    if (!index.isValid())
    {
        emit statusUpdateMessage("No item selected", 3000);
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
        );

    if (fileName.isEmpty())
        return;

    QFileInfo info(fileName);

    ModelPart* part =
        static_cast<ModelPart*>(index.internalPointer());

    if (!part)
        return;

    //Update column 0 (Name)
    part->set(0, info.fileName());

    //Refresh tree view
    ui->treeView->viewport()->update();

    emit statusUpdateMessage(
        "Item renamed to: " + info.fileName(),
        3000
        );
}

void MainWindow::openContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    if (!index.isValid()) return;

    ModelPart *part =
        static_cast<ModelPart*>(index.internalPointer());

    if (!part) return;

    QMenu menu(this);
    QAction *editAction = menu.addAction("Edit Properties");

    QAction *selected =
        menu.exec(ui->treeView->viewport()->mapToGlobal(pos));

    if (selected == editAction)
    {
        PartPropertiesDialog dialog(this);
        dialog.setModelPart(part);

        if (dialog.exec() == QDialog::Accepted)
        {
            ui->treeView->viewport()->update();
            emit statusUpdateMessage("Item properties updated", 3000);
        }
    }
}
