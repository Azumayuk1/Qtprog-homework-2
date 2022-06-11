#ifndef LAYER_H
#define LAYER_H
//Lowest element in hierarchy, small box

#include <QString>
#include <QVector>

class layer
{
public:
    layer();
    layer(QString layerData, QString pointerLinked);
    layer(QString layerData);

    QString layerData; //Label, string
    QString pointerLinked; //Points to other layer

};

#endif // LAYER_H
