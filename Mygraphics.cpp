#include "Mygraphics.h"

Mygraphics::Mygraphics()
{
}

bool Mygraphics::graphicsLoad(QString fileName)
{
    QFile loadFile(fileName);

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open this file.");
        return false;
    }
    qDebug()<<fileName;

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject json = loadDoc.object();
    //
    tiersSavedVectorSize = json["tiersVectorSize"].toInt();
    qDebug()<<"tiers Saved vector size: "<<tiersSavedVectorSize;
    //
    QJsonArray data = json["tiersVector"].toArray();

    qDebug()<<"-for cycle started-";
    for(int i = 0; i < tiersSavedVectorSize; i++)
    {
        QJsonArray level = data[i].toArray();
        qDebug()<<level[0].toString();
        qDebug()<<"-level array created-";

        tiersSavedVector.append(Tier(level[0].toString(),level[1].toInt()));

        int temp_array_count = 0;
        QJsonArray layersData = level[2].toArray();
        for(int j = 0; j < tiersSavedVector[i].tierLayersSize;j++){
            qDebug()<<"for j cycle started: j ="<<j;

            tiersSavedVector[i].tierLayers[j].layerData = layersData[temp_array_count].toString();
            tiersSavedVector[i].tierLayers[j].pointerLinked = layersData[temp_array_count+1].toString();
            temp_array_count+=2;
            qDebug()<<"for j cycle ended: ";

        }
    }

    return true;
}


