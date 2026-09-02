// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaSubterranea.h"

APlataformaSubterranea::APlataformaSubterranea()
{
	PrimaryActorTick.bCanEverTick = true;
	TipoPlataforma = ETipoPlataforma::PLATAFORMA_SUBTERRANEA;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlataformaMeshAsset(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'")
	);

	if (PlataformaMeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(PlataformaMeshAsset.Object);
	}

	movimientoEjes = FVector(1.0f, 0.0f, 1.0f);
	movimientoLimitesMaximos = FVector(0.0f, 0.0f, 900.0f);
	movimientoLimitesMinimos = FVector(0.0f, 0.0f, 0.0f);
	movimientoVelocidades = FVector(0.0f, 0.0f, 500.0f);
	movimientoDireccion = FVector(1.0f, 0.0f, 1.0f);
}