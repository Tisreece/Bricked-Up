#include "BrickGolden.h"
#include "Materials/MaterialInstanceDynamic.h"

ABrickGolden::ABrickGolden()
{
    MaxHealth = 5;
    Value = 100.0f;
}

void ABrickGolden::BeginPlay()
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

void ABrickGolden::SetNewMaterial()
{
    if (Health == 5)
    {
        return;
    }
    else if (Health == 4)
    {
        DynMaterial->SetScalarParameterValue("Brightness", 1.4f);
        DynMaterial->SetScalarParameterValue("Contrast", -0.05f);
    }
    else if (Health == 3)
    {
        DynMaterial->SetScalarParameterValue("Brightness", 1.8f);
        DynMaterial->SetScalarParameterValue("Contrast", -0.1f);
    }
    else if (Health == 2)
    {
        DynMaterial->SetScalarParameterValue("Brightness", 2.2f);
        DynMaterial->SetScalarParameterValue("Contrast", -0.15f);
    }
    else if (Health == 1)
    {
        DynMaterial->SetScalarParameterValue("Brightness", 2.6f);
        DynMaterial->SetScalarParameterValue("Contrast", -0.2f);
    }
}