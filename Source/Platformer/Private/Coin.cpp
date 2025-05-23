// © 2024 Anaheim-RX78. All rights reserved.


#include "Coin.h"

#include "Kismet/GameplayStatics.h"
#include "Platformer/PlatformerCharacter.h"

class APlatformerCharacter;

ACoin::ACoin() {
	this->PrimaryActorTick.bCanEverTick = true;

	this->Mesh = this->CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	this->Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);

	this->SetRootComponent(this->Mesh);
}

void ACoin::BeginPlay() {
	Super::BeginPlay();

	this->InitialPosition = this->GetActorLocation();
	this->TargetPosition = this->GetActorLocation() + this->DeltaMovement;
}

void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	APlatformerCharacter* Character = Cast<APlatformerCharacter>(OtherActor);
	if (IsValid(Character)) {
		if (SoundEffect) {
			UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), this->SoundEffect, this->GetActorLocation());
		}
		Character->Coins++;

		this->Disappear();
	}
}

void ACoin::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);

	this->Time += DeltaTime * this->Speed;
	const float t = 0.5f - 0.5f * FMath::Cos(this->Time);

	this->SetActorLocation(FMath::Lerp(this->InitialPosition, this->TargetPosition, t));
}
