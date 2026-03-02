#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ModelPart.h"
#include "ModelPartList.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void statusUpdateMessage(const QString &message, int timeout);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleButton1();

public slots:
    void handleTreeClicked(const QModelIndex &index);

private slots:
    void on_actionOpen_File_triggered();

private slots:
    void openContextMenu(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;
};
#endif // MAINWINDOW_H
