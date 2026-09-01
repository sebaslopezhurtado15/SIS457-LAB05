// Copyright Epic Games, Inc. All Rights Reserved.

// LABORATORIO 04 - SIS457
// GRUPO 4
// Control de 200 plataformas, temporizadores y eliminacion aleatoria


#include "AventuraUSFX022026L4GameMode.h"
#include "AventuraUSFX022026L4Pawn.h"
#include "Engine/World.h"
#include "Plataforma.h"
#include "PlataformaAerea.h"
#include "PlataformaAcuatica.h"
#include "PlataformaTerrestre.h"
#include "PlataformaSubterranea.h"


AAventuraUSFX022026L4GameMode::AAventuraUSFX022026L4GameMode()
{
	DefaultPawnClass =
		AAventuraUSFX022026L4Pawn::StaticClass();
}

void AAventuraUSFX022026L4GameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return;
	}

	FRotator Rotacion(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters Parametros;

	Parametros.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	aPlataformas.Reserve(200);



	for (int32 i = 0; i < 200; i++)
	{
		FVector SpawnLocation(
			FMath::RandRange(-1500.0f, 1500.0f),
			FMath::RandRange(-1500.0f, 1500.0f),
			FMath::RandRange(1200.0f, 1600.0f)
		);

		APlataforma* Plataforma =
			World->SpawnActor<APlataforma>(
				SpawnLocation,
				Rotacion,
				Parametros
				);

		if (IsValid(Plataforma))
		{

			Plataforma->ConfigurarMovimiento(i % 10);


			aPlataformas.Add(Plataforma);
		}
	}
	GetWorldTimerManager().SetTimer(
		TimerMovimiento,
		this,
		&AAventuraUSFX022026L4GameMode::IniciarMovimiento,
		5.0f,
		false
	);
}

void AAventuraUSFX022026L4GameMode::IniciarMovimiento()
{

	if (aPlataformas.Num() == 0)
	{
		return;
	}


	for (APlataforma* Plataforma : aPlataformas)
	{
		if (IsValid(Plataforma))
		{
			Plataforma->IniciarMovimiento();
		}
	}



	GetWorldTimerManager().SetTimer(
		TimerEliminar,
		this,
		&AAventuraUSFX022026L4GameMode::EliminarPlataforma,
		0.3f,
		true
	);

	GetWorldTimerManager().SetTimer(
		TimerMovimiento,
		this,
		&AAventuraUSFX022026L4GameMode::DetenerMovimiento,
		10.0f,
		false
	);
}

void AAventuraUSFX022026L4GameMode::DetenerMovimiento()
{
	GetWorldTimerManager().ClearTimer(TimerEliminar);


	if (aPlataformas.Num() == 0)
	{
		return;
	}

	for (APlataforma* Plataforma : aPlataformas)
	{
		if (IsValid(Plataforma))
		{
			Plataforma->DetenerMovimiento();
		}
	}

	GetWorldTimerManager().SetTimer(
		TimerMovimiento,
		this,
		&AAventuraUSFX022026L4GameMode::IniciarMovimiento,
		5.0f,
		false
	);
}

void AAventuraUSFX022026L4GameMode::EliminarPlataforma()
{
	if (aPlataformas.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerEliminar);
		return;
	}

	int32 Indice =
		FMath::RandRange(
			0,
			aPlataformas.Num() - 1
		);

	APlataforma* Plataforma =
		aPlataformas[Indice];

	if (IsValid(Plataforma))
	{
		Plataforma->Destroy();
	}

	aPlataformas.RemoveAt(Indice);

	if (aPlataformas.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerEliminar);
		GetWorldTimerManager().ClearTimer(TimerMovimiento);
	}
}