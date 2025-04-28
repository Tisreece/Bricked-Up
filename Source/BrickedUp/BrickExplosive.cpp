#include "BrickExplosive.h"

ABrickExplosive::ABrickExplosive()
{
    MaxHealth = 1;
    Value = 10.0f;
}

void ABrickExplosive::Explode(TArray<ABrickMaster*> BricksToExplode)
{
    for (ABrickMaster* MarkedBrick : BricksToExplode)
    {
        if (MarkedBrick)
        {
            MarkedBrick->DestroyBrick();
        }
    }
}