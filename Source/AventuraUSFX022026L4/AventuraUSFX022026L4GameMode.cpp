// Copyright Epic Games, Inc. All Rights Reserved.

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
	DefaultPawnClass = AAventuraUSFX022026L4Pawn::StaticClass();
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

	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	aPlataformas.Reserve(25);

	for (int32 i = 0; i < 10; i++)
	{
		int32 Fila = i / 5;
		int32 Columna = i % 5;

		FVector SpawnLocation(-800.0f + Columna * 400.0f, -800.0f + Fila * 400.0f, 1400.0f);

		APlataformaAerea* Plataforma = World->SpawnActor<APlataformaAerea>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(Plataforma))
		{
			aPlataformas.Add(Plataforma);
		}
	}

	for (int32 i = 0; i < 6; i++)
	{
		FVector SpawnLocation(-1000.0f + i * 400.0f, 200.0f, 100.0f);

		APlataformaTerrestre* Plataforma = World->SpawnActor<APlataformaTerrestre>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(Plataforma))
		{
			aPlataformas.Add(Plataforma);
		}
	}

	for (int32 i = 0; i < 4; i++)
	{
		int32 Fila = i / 2;
		int32 Columna = i % 2;

		FVector SpawnLocation(-200.0f + Columna * 400.0f, 600.0f + Fila * 400.0f, -400.0f);

		APlataformaSubterranea* Plataforma = World->SpawnActor<APlataformaSubterranea>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(Plataforma))
		{
			aPlataformas.Add(Plataforma);
		}
	}

	for (int32 i = 0; i < 5; i++)
	{
		FVector SpawnLocation(-800.0f + i * 400.0f, 1400.0f, 300.0f);

		APlataformaAcuatica* Plataforma = World->SpawnActor<APlataformaAcuatica>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(Plataforma))
		{
			aPlataformas.Add(Plataforma);
		}
	}

	GetWorldTimerManager().SetTimer(TimerMovimiento, this, &AAventuraUSFX022026L4GameMode::IniciarMovimiento, 5.0f, false);

	GetWorldTimerManager().SetTimer(TimerEliminarHija, this, &AAventuraUSFX022026L4GameMode::EliminarUnaPlataformaPorHija, 5.0f, true);
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

	GetWorldTimerManager().SetTimer(TimerMovimiento, this, &AAventuraUSFX022026L4GameMode::DetenerMovimiento, 10.0f, false);
}

void AAventuraUSFX022026L4GameMode::EliminarUnaPlataformaPorHija()
{
	for (int32 i = 0; i < aPlataformas.Num(); i++)
	{
		APlataformaAerea* Aerea = Cast<APlataformaAerea>(aPlataformas[i]);

		if (IsValid(Aerea))
		{
			Aerea->Destroy();
			aPlataformas.RemoveAt(i);
			break;
		}
	}

	for (int32 i = 0; i < aPlataformas.Num(); i++)
	{
		APlataformaTerrestre* Terrestre = Cast<APlataformaTerrestre>(aPlataformas[i]);

		if (IsValid(Terrestre))
		{
			Terrestre->Destroy();
			aPlataformas.RemoveAt(i);
			break;
		}
	}

	for (int32 i = 0; i < aPlataformas.Num(); i++)
	{
		APlataformaSubterranea* Subterranea = Cast<APlataformaSubterranea>(aPlataformas[i]);

		if (IsValid(Subterranea))
		{
			Subterranea->Destroy();
			aPlataformas.RemoveAt(i);
			break;
		}
	}

	for (int32 i = 0; i < aPlataformas.Num(); i++)
	{
		APlataformaAcuatica* Acuatica = Cast<APlataformaAcuatica>(aPlataformas[i]);

		if (IsValid(Acuatica))
		{
			Acuatica->Destroy();
			aPlataformas.RemoveAt(i);
			break;
		}
	}

	if (aPlataformas.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerEliminarHija);
		GetWorldTimerManager().ClearTimer(TimerMovimiento);
	}
}

void AAventuraUSFX022026L4GameMode::DetenerMovimiento()
{
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

	GetWorldTimerManager().SetTimer(TimerMovimiento, this, &AAventuraUSFX022026L4GameMode::IniciarMovimiento, 5.0f, false);
}