#include "BrickSmashable.h"
#include "Materials/MaterialInstanceDynamic.h"

ABrickSmashable::ABrickSmashable()
{
    MaxHealth = 3;
    Value = 30.0f;
}

void ABrickSmashable::BeginPlay()
{
    Super::BeginPlay();

    UMaterialInterface* CurrentMat = Brick->GetMaterial(0);
    if (CurrentMat)
    {
        DynMaterial = UMaterialInstanceDynamic::Create(CurrentMat, this);
        Brick->SetMaterial(0, DynMaterial);

        DynMaterial->SetScalarParameterValue("Brightness", 1.0f);
        DynMaterial->SetScalarParameterValue("Contrast", 0.0f);
    }
}

void ABrickSmashable::SetNewMaterial()
{
    if (Health == 3)
    {
        return;
    }
    else if (Health == 2)
    {
        DynMaterial->SetScalarParameterValue("Brightness", 3.0f);
        DynMaterial->SetScalarParameterValue("Contrast", 0.1f);
    }
    else if (Health == 1)
    {
        DynMaterial->SetScalarParameterValue("Brightness", 6.0f);
        DynMaterial->SetScalarParameterValue("Contrast", 0.2f);
    }
}