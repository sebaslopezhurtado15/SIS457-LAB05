// LABORATORIO 04 - SIS457
// GRUPO 4

// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

class UStaticMeshComponent;

enum class ETipoPlataforma
{
	PLATAFORMA_TERRESTRE,
	PLATAFORMA_AEREA,
	PLATAFORMA_SUBTERRANEA,
	PLATAFORMA_ACUATICA,
};


UCLASS()
class AVENTURAUSFX022026L4_API APlataforma : public AActor
{
	GENERATED_BODY()

public:
	APlataforma();

	virtual void Tick(float DeltaTime) override;

	// Asigna uno de los 10 tipos de movimiento
	void ConfigurarMovimiento(int32 Tipo);

	void IniciarMovimiento();
	void DetenerMovimiento();

	ETipoPlataforma TipoPlataforma;

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* mallaPlataforma;

	FVector movimientoEjes;
	FVector movimientoLimitesMaximos;
	FVector movimientoLimitesMinimos;
	FVector movimientoVelocidades;
	FVector movimientoDireccion;
	FVector posicionActual;
	FVector posicionInicial;

	bool bMover;
};