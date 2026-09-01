// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "AventuraUSFX022026L4GameMode.generated.h"

class APlataforma;

UCLASS(MinimalAPI)
class AAventuraUSFX022026L4GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAventuraUSFX022026L4GameMode();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY()
		TArray<APlataforma*> aPlataformas;

	FTimerHandle TimerMovimiento;
	FTimerHandle TimerEliminarHija;

	void IniciarMovimiento();
	void DetenerMovimiento();
	void EliminarUnaPlataformaPorHija();
};