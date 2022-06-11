#ifndef TIER_H
#define TIER_H
//Contains layers, big box

#include <layer.h>
#include <QHash>

class Tier
{
public:
    Tier();//Different cases constructors
    Tier(QString tierName, QVector<layer> tierLayers);
    Tier(QString tierName, int tierLayersSize);

    QString tierName; //Name (label)
    QVector<layer> tierLayers; //Layers contained by tier
    int tierLayersSize;


};

#endif // TIER_H
