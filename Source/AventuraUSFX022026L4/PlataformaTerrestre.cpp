// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaTerrestre.h"
#include "Components/BoxComponent.h"

APlataformaTerrestre::APlataformaTerrestre()
{
	PrimaryActorTick.bCanEverTick = true;
	TipoPlataforma = ETipoPlataforma::PLATAFORMA_TERRESTRE;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlataformaMeshAsset(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")
	);

	if (PlataformaMeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(PlataformaMeshAsset.Object);
	}

	// Zona para la colision Overlap
	ZonaOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaOverlap"));
	ZonaOverlap->SetupAttachment(RootComponent);

	ZonaOverlap->SetBoxExtent(FVector(250.0f, 250.0f, 150.0f));

	ZonaOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ZonaOverlap->SetCollisionResponseToAllChannels(ECR_Ignore);
	ZonaOverlap->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ZonaOverlap->SetGenerateOverlapEvents(true);

	ZonaOverlap->OnComponentBeginOverlap.AddDynamic(
		this,
		&APlataformaTerrestre::AlEntrarZona
	);

	ZonaOverlap->OnComponentEndOverlap.AddDynamic(
		this,
		&APlataformaTerrestre::AlSalirZona
	);

	movimientoEjes = FVector(0.0f, 1.0f, 0.0f);
	movimientoLimitesMaximos = FVector(0.0f, 500.0f, 0.0f);
	movimientoLimitesMinimos = FVector(0.0f, 0.0f, 0.0f);
	movimientoVelocidades = FVector(0.0f, 500.0f, 0.0f);
	movimientoDireccion = FVector(0.0f, 1.0f, 0.0f);
}

void APlataformaTerrestre::AlEntrarZona(UPrimitiveComponent* Componente,AActor* OtroActor,UPrimitiveComponent* OtroComponente,int32 OtroIndice,bool bFromSweep,const FHitResult& SweepResult)
{
	if (OtroActor != nullptr && OtroActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("COLISION OVERLAP: jugador entro en la zona"));
	}
}

void APlataformaTerrestre::AlSalirZona(
	UPrimitiveComponent* Componente,
	AActor* OtroActor,
	UPrimitiveComponent* OtroComponente,
	int32 OtroIndice)
{
	if (OtroActor != nullptr && OtroActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("COLISION OVERLAP: jugador salio de la zona"));
	}
}