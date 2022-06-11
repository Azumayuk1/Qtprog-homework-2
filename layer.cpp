#include "layer.h"

layer::layer()
{
    layerData = NULL;
    pointerLinked = NULL;
}

layer::layer(QString layerData,QString pointerLinked)
{
    this->layerData = layerData;
    this->pointerLinked = pointerLinked;
}

layer::layer(QString layerData)
{
    this->layerData = layerData;
    pointerLinked = NULL;
}
