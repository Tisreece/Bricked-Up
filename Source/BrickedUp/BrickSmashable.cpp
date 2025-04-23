#include "BrickSmashable.h"

ABrickSmashable::ABrickSmashable()
{
    MaxHealth = 3;
    Value = 30.0f;
}

void ABrickSmashable::SetNewMaterial()
{
    if (Health == 3)
    {
        return;
    }
    else if (Health == 2)
    {
        Brick->SetMaterial(0, HealthMaterial2);
    }
    else if (Health == 1)
    {
        Brick->SetMaterial(0, HealthMaterial1);
    }
}