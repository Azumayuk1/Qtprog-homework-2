#ifndef MYDIAGRAM_H
#define MYDIAGRAM_H
//Diagram drawing and window

#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

#include <Mygraphics.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MyDiagram; }
QT_END_NAMESPACE

class MyDiagram : public QWidget
{
    Q_OBJECT

public:
    MyDiagram(QWidget *parent = nullptr);
    ~MyDiagram();
    QGraphicsScene *newScene;

    void draw_diagram(QVector<Tier>tiersSavedVector);

private:
    Ui::MyDiagram *ui;
};
#endif // MYDIAGRAM_H
