// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plataforma.h"
#include "PlataformaTerrestre.generated.h"

class UBoxComponent;


UCLASS()
class AVENTURAUSFX022026L4_API APlataformaTerrestre : public APlataforma
{
	GENERATED_BODY()

public:
	APlataformaTerrestre();

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* ZonaOverlap;

	UFUNCTION()
		void AlEntrarZona(UPrimitiveComponent* Componente,AActor* OtroActor,UPrimitiveComponent* OtroComponente,int OtroIndice,bool bFromSweep,const FHitResult& SweepResult);

	UFUNCTION()
		void AlSalirZona(UPrimitiveComponent* Componente,AActor* OtroActor,UPrimitiveComponent* OtroComponente,int OtroIndice);

	//efecto billar
	UFUNCTION()
		void AlRecibirImpacto(UPrimitiveComponent* ComponenteGolpeado,AActor* OtroActor,UPrimitiveComponent* OtroComponente,FVector ImpulsoNormal,const FHitResult& Hit);
};
