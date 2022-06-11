#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//Main window

#include <QMainWindow>
#include <QFileDialog>
#include <QString>

#include <Mygraphics.h>
#include <mydiagram.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Mygraphics NewGraphics;
    MyDiagram *newDiagram;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public  slots:
    void  load();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
