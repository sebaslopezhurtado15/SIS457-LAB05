// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaSubterranea.h"
#include "Components/BoxComponent.h"


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

	//colision Block
	ColisionBlock = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisionBlock"));
	ColisionBlock->SetupAttachment(mallaPlataforma);
	ColisionBlock->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	ColisionBlock->SetCollisionProfileName(TEXT("BlockAll"));


	//overlapS
	ZonaOverlapS = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaOverlapS"));
	ZonaOverlapS->SetupAttachment(mallaPlataforma);
	ZonaOverlapS->SetBoxExtent(FVector(300.0f, 300.0f, 150.0f));
	ZonaOverlapS->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ZonaOverlapS->SetCollisionResponseToAllChannels(ECR_Ignore);
	ZonaOverlapS->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ZonaOverlapS->SetGenerateOverlapEvents(true);
	ZonaOverlapS->OnComponentBeginOverlap.AddDynamic(this, &APlataformaSubterranea::AlEntrarZona);
	ZonaOverlapS->OnComponentEndOverlap.AddDynamic(this, &APlataformaSubterranea::AlSalirZona);


	movimientoEjes = FVector(1.0f, 0.0f, 1.0f);
	movimientoLimitesMaximos = FVector(0.0f, 0.0f, 800.0f);
	movimientoLimitesMinimos = FVector(0.0f, 0.0f, -100.0f);
	movimientoVelocidades = FVector(0.0f, 0.0f, 400.0f);
	movimientoDireccion = FVector(1.0f, 0.0f, 1.0f);
}

//Efecto lentitud
void APlataformaSubterranea::AlEntrarZona(UPrimitiveComponent* Componente, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int OtroIndice, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtroActor != nullptr && OtroActor != this)
	{
		OtroActor->CustomTimeDilation = 0.3f;
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP SUBTERRANEA: jugador entro en la zona"));
	}
}

void APlataformaSubterranea::AlSalirZona(UPrimitiveComponent* Componente, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int OtroIndice)
{
	if (OtroActor != nullptr && OtroActor != this)
	{
		OtroActor->CustomTimeDilation = 1.0f;
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP SUBTERRANEA: jugador salio de la zona"));
	}
}