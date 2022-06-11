#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Mygraphics.h>
#include <mydiagram.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_Load, &QPushButton::clicked,
                                        this, &MainWindow::load);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    QString fileName = QFileDialog::getOpenFileName(this);
        if(fileName.isEmpty()){return;}
    NewGraphics.graphicsLoad(fileName);

    newDiagram = new MyDiagram;
    newDiagram->draw_diagram(NewGraphics.tiersSavedVector);
    newDiagram->show();

}

