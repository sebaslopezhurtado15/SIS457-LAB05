// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plataforma.h"
#include "PlataformaSubterranea.generated.h"

class UBoxComponent;


UCLASS()
class AVENTURAUSFX022026L4_API APlataformaSubterranea : public APlataforma
{
	GENERATED_BODY()

public:
	APlataformaSubterranea();

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* ColisionBlock;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* ZonaOverlapS;

	UFUNCTION()
		void AlEntrarZona(UPrimitiveComponent* Componente, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int OtroIndice, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void AlSalirZona(UPrimitiveComponent* Componente, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int OtroIndice);

};