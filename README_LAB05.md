# LABORATORIO 05 — SIS457 - Grupo 4

Proyecto desarrollado en Unreal Engine 4.27.2 utilizando C++.

El laboratorio implementa colisiones y efectos dentro del proyecto AventuraUSFX. Se utilizan colisiones de tipo `Block` y `Overlap` para detectar impactos y zonas de interacción, además de efectos aplicados a la plataforma terrestre y a la plataforma subterránea.

---

## 1. Objetivo del proyecto

Implementar un sistema de colisiones y efectos aplicando conceptos de C++ y Unreal Engine 4.27.2, utilizando:

- `UStaticMeshComponent`.
- `UBoxComponent`.
- `UPROPERTY`.
- `UFUNCTION`.
- `OnComponentHit`.
- `OnComponentBeginOverlap`.
- `OnComponentEndOverlap`.
- `AddDynamic`.
- Perfiles de colisión.
- `BlockAll`.
- `QueryOnly`.
- `ECR_Ignore`.
- `ECR_Overlap`.
- `ECC_Pawn`.
- `FVector`.
- `GetVelocity()`.
- `GetSafeNormal()`.
- `CustomTimeDilation`.
- `Tick()`.
- `UE_LOG`.

---

## 2. Funcionalidades implementadas

El laboratorio cumple con las siguientes funcionalidades:

1. El proyectil utiliza una colisión de tipo `Block` al impactar contra superficies bloqueantes.
2. La plataforma terrestre detecta la entrada y salida de la nave mediante una zona `Overlap`.
3. La plataforma subterránea utiliza un `UBoxComponent` adicional para asegurar el bloqueo del proyectil.
4. La plataforma subterránea posee una zona `Overlap` independiente.
5. Cuando un proyectil impacta la plataforma terrestre, se activa un efecto tipo billar.
6. La dirección inicial del movimiento de la plataforma terrestre depende de la dirección del proyectil.
7. La plataforma terrestre reutiliza el sistema de movimiento y límites existente en `APlataforma`.
8. Cuando la nave entra en la zona `Overlap` de la plataforma subterránea, su movimiento se vuelve más lento.
9. Cuando la nave sale de la zona subterránea, recupera su velocidad normal.
10. Se utilizan mensajes con `UE_LOG` para comprobar los eventos de colisión durante la ejecución.

---

## 3. Colisión Block

La clase `APlataforma` utiliza una malla principal configurada con el perfil de colisión:

```cpp
mallaPlataforma->SetCollisionProfileName(TEXT("BlockAll"));
```

El proyectil posee su propio perfil de colisión y utiliza el evento:

```cpp
ProjectileMesh->OnComponentHit.AddDynamic(
    this,
    &AAventuraUSFX022026L4Projectile::OnHit
);
```

Cuando ocurre un impacto se ejecuta `OnHit()` y el proyectil se elimina mediante:

```cpp
Destroy();
```

También se utiliza `UE_LOG` para comprobar que ocurrió la colisión.

---

## 4. Plataforma terrestre

La plataforma terrestre utiliza una zona invisible de tipo `UBoxComponent`:

```cpp
UPROPERTY(VisibleAnywhere)
UBoxComponent* ZonaOverlap;
```

La zona se configura para detectar únicamente al `Pawn`:

```cpp
ZonaOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
ZonaOverlap->SetCollisionResponseToAllChannels(ECR_Ignore);
ZonaOverlap->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
ZonaOverlap->SetGenerateOverlapEvents(true);
```

Los eventos de entrada y salida se conectan mediante:

```cpp
ZonaOverlap->OnComponentBeginOverlap.AddDynamic(
    this,
    &APlataformaTerrestre::AlEntrarZona
);

ZonaOverlap->OnComponentEndOverlap.AddDynamic(
    this,
    &APlataformaTerrestre::AlSalirZona
);
```

De esta forma se puede detectar cuándo la nave entra y cuándo sale de la zona.

### Efecto billar

La plataforma terrestre también responde al impacto mediante:

```cpp
UFUNCTION()
void AlRecibirImpacto(
    UPrimitiveComponent* ComponenteGolpeado,
    AActor* OtroActor,
    UPrimitiveComponent* OtroComponente,
    FVector ImpulsoNormal,
    const FHitResult& Hit
);
```

Cuando recibe el proyectil se obtiene la dirección del disparo:

```cpp
FVector DireccionDisparo = OtroActor->GetVelocity();
DireccionDisparo.Z = 0.0f;
DireccionDisparo = DireccionDisparo.GetSafeNormal();
```

Luego esa dirección se utiliza para modificar el movimiento:

```cpp
movimientoDireccion = DireccionDisparo;
```

Finalmente se inicia el movimiento mediante:

```cpp
IniciarMovimiento();
```

El `Tick()` de `APlataforma` continúa controlando el desplazamiento y el cambio de dirección cuando se alcanzan los límites establecidos.

---

## 5. Plataforma subterránea

Para asegurar el bloqueo del proyectil en la plataforma subterránea se agregó una caja independiente:

```cpp
UPROPERTY(VisibleAnywhere)
UBoxComponent* ColisionBlock;
```

Su configuración principal es:

```cpp
ColisionBlock = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisionBlock"));
ColisionBlock->SetupAttachment(mallaPlataforma);
ColisionBlock->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
ColisionBlock->SetCollisionProfileName(TEXT("BlockAll"));
```

También se agregó una segunda caja para el `Overlap`:

```cpp
UPROPERTY(VisibleAnywhere)
UBoxComponent* ZonaOverlapS;
```

Su configuración permite detectar al `Pawn` sin bloquearlo:

```cpp
ZonaOverlapS->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
ZonaOverlapS->SetCollisionResponseToAllChannels(ECR_Ignore);
ZonaOverlapS->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
ZonaOverlapS->SetGenerateOverlapEvents(true);
```

### Efecto de lentitud

Cuando la nave entra en la zona subterránea se modifica su tiempo individual:

```cpp
OtroActor->CustomTimeDilation = 0.3f;
```

Cuando sale se restaura el valor normal:

```cpp
OtroActor->CustomTimeDilation = 1.0f;
```

Así, la nave se mueve más lentamente mientras permanece dentro de la zona `Overlap`.

---

## 6. Funcionamiento

```text
Inicio
  |
  v
Nave y plataformas en el escenario
  |
  +------------------------------+
  |                              |
  v                              v
Plataforma terrestre       Plataforma subterránea
  |                              |
  |                              +--> ColisionBlock
  |                              |        |
  |                              |        v
  |                              |    Proyectil bloqueado
  |                              |
  +--> ZonaOverlap               +--> ZonaOverlapS
  |        |                               |
  |        v                               v
  |   Entrada / salida               Nave entra en zona
  |                                          |
  +--> Proyectil impacta                    v
           |                        CustomTimeDilation = 0.3
           v                                |
    AlRecibirImpacto()                      v
           |                           Nave más lenta
           v                                |
 Obtener dirección                          v
   del proyectil                       Nave sale
           |                                |
           v                                v
  Efecto tipo billar              CustomTimeDilation = 1.0
```

---

## 7. Archivos principales

```text
Source/AventuraUSFX022026L4/
│
├── Plataforma.h
├── Plataforma.cpp
│
├── PlataformaTerrestre.h
├── PlataformaTerrestre.cpp
│
├── PlataformaSubterranea.h
├── PlataformaSubterranea.cpp
│
├── AventuraUSFX022026L4Projectile.h
├── AventuraUSFX022026L4Projectile.cpp
│
└── AventuraUSFX022026L4Pawn.cpp
```

---

## 8. Tecnologías utilizadas

- C++.
- Unreal Engine 4.27.2.
- Visual Studio 2019.
- Git.
- GitHub.
- Git LFS.

---

## 9. Ejecución

1. Abrir `AventuraUSFX022026L4.uproject` con Unreal Engine 4.27.2.
2. Compilar el código C++.
3. Ejecutar el nivel.
4. Disparar contra la plataforma terrestre para observar el efecto tipo billar.
5. Disparar contra la plataforma subterránea para comprobar la colisión `Block`.
6. Entrar y salir de las zonas `Overlap` para comprobar los eventos.
7. Entrar en la zona de la plataforma subterránea para observar la reducción de velocidad de la nave.
8. Revisar el `Output Log` para observar los mensajes generados con `UE_LOG`.

---

## 10. Repositorio

https://github.com/sebaslopezhurtado15/SIS457-LAB05
