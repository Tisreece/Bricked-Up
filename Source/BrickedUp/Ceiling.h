#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Ceiling.generated.h"

UCLASS()
class BRICKEDUP_API ACeiling : public AActor
{
    GENERATED_BODY()
protected:
    virtual void BeginPlay() override;

    UFUNCTION() void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
    UFUNCTION(BlueprintCallable, Category="Hit") 
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    ACeiling(); 
    virtual void Tick(float DeltaTime) override;

    //Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components") class UBoxComponent* CollisionBox;

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") USoundBase* HitAudio;

    //Functions
    

};