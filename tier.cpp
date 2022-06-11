#include "tier.h"

Tier::Tier()
{
    tierName = "No_Tier";
    tierLayersSize = 0;
}

Tier::Tier(QString tierName, QVector<layer> tierLayers)
{
    this->tierName = tierName;
    this->tierLayers = tierLayers;
    tierLayersSize = tierLayers.size();
}

Tier::Tier(QString tierName, int tierLayersSize)
{
    this->tierName = tierName;
    this->tierLayersSize = tierLayersSize;
    tierLayers.resize(tierLayersSize);
}
