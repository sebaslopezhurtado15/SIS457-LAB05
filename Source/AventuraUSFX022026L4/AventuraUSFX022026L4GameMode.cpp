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

	aPlataformas.Reserve(31);
	APlataforma* PlataformaActual;


	for (int32 i = 0; i < 10; i++)
	{
		int32 Fila = i / 5;
		int32 Columna = i % 5;

		FVector SpawnLocation(-800.0f + Columna * 400.0f, -800.0f + Fila * 400.0f, 1400.0f);

		PlataformaActual = World->SpawnActor<APlataformaAerea>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(PlataformaActual))
		{
			aPlataformas.Add(PlataformaActual);
		}
	}

	for (int32 i = 0; i < 6; i++)
	{
		FVector SpawnLocation(-1000.0f + i * 400.0f, 200.0f, 100.0f);

		PlataformaActual = World->SpawnActor<APlataformaTerrestre>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(PlataformaActual))
		{
			aPlataformas.Add(PlataformaActual);
		}
	}

	for (int32 i = 0; i < 4; i++)
	{
		int32 Fila = i / 2;
		int32 Columna = i % 2;

		FVector SpawnLocation(-200.0f + Columna * 400.0f, 600.0f + Fila * 400.0f, -400.0f);

		PlataformaActual = World->SpawnActor<APlataformaSubterranea>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(PlataformaActual))
		{
			aPlataformas.Add(PlataformaActual);
		}
	}

	for (int32 i = 0; i < 5; i++)
	{
		FVector SpawnLocation(-500.0f + i * 400.0f, 1400.0f, 300.0f);

		PlataformaActual = World->SpawnActor<APlataformaAcuatica>(SpawnLocation, Rotacion, Parametros);

		if (IsValid(PlataformaActual))
		{
			aPlataformas.Add(PlataformaActual);
		}
	}

	for (int32 i = 0; i < 6; i++)
	{
		FVector SpawnLocation(-130.0f + i * 300.0f, -134.0f, 160.0f);

		int32 TipoAleatorio = FMath::RandRange(1, 4);

		switch (TipoAleatorio)
		{
		case 1:
			PlataformaActual = World->SpawnActor<APlataformaAerea>(SpawnLocation, Rotacion, Parametros);
			break;

		case 2:
			PlataformaActual = World->SpawnActor<APlataformaTerrestre>(SpawnLocation, Rotacion, Parametros);
			break;

		case 3:
			PlataformaActual = World->SpawnActor<APlataformaSubterranea>(SpawnLocation, Rotacion, Parametros);
			break;

		case 4:
			PlataformaActual =
				World->SpawnActor<APlataformaAcuatica>(SpawnLocation, Rotacion, Parametros);
			break;
		}

		if (IsValid(PlataformaActual))
		{
			aPlataformas.Add(PlataformaActual);
		}
	}

	GetWorldTimerManager().SetTimer(TimerMovimiento, this, &AAventuraUSFX022026L4GameMode::IniciarMovimiento, 5.0f, false);

	/*GetWorldTimerManager().SetTimer(TimerEliminarUnaPlataformaPorHija, this, &AAventuraUSFX022026L4GameMode::EliminarUnaPlataformaPorHija, 5.0f, true);*/

	GetWorldTimerManager().SetTimer(TimerReposicionarPlataformas, this, &AAventuraUSFX022026L4GameMode::ReposicionarPlataformas, 5.0f, false);
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
		GetWorldTimerManager().ClearTimer(TimerEliminarUnaPlataformaPorHija);
		GetWorldTimerManager().ClearTimer(TimerMovimiento);
		GetWorldTimerManager().ClearTimer(TimerReposicionarPlataformas);

	}
}

void AAventuraUSFX022026L4GameMode::ReposicionarPlataformas()
{
	FVector posicionAereos = FVector(-1090.0f, -1310.0f, 200.0f);
	FVector posicionTerrestres = FVector(-1030.0f, -1220.0f, 200.0f);

	for (APlataforma* plataformaActual : aPlataformas)
	{
		if (plataformaActual->TipoPlataforma == ETipoPlataforma::PLATAFORMA_AEREA)
		{
			plataformaActual->SetActorLocation(posicionAereos);
		}

		if (plataformaActual->TipoPlataforma == ETipoPlataforma::PLATAFORMA_TERRESTRE)
		{
			plataformaActual->SetActorLocation(posicionTerrestres);
		}

	}

}

