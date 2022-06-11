#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H
//Loads files

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>


#include <tier.h>

class Mygraphics
{
public:
    Mygraphics();

    QVector<Tier> tiersSavedVector;//Vector of tiers
    int tiersSavedVectorSize;//Size of vector

    bool graphicsLoad(QString fileName);
    //void graphicsShow( );
};

#endif // MYGRAPHICS_H
