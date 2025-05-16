// Fill out your copyright notice in the Description page of Project Settings.


#include "AVoidPlatform.h"

AAVoidPlatform::AAVoidPlatform(): AAMovingPlatform() {
	this->Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	this->Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AAVoidPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult) {
	if (!this->IsEnabled) {
		return;
	}

	APlatformerCharacter* Character = static_cast<APlatformerCharacter*>(OtherActor);
	if (IsValid(Character)) {
		this->PlaySound(0.f);
		this->MakeDamage(Character, EDamageTypes::Void);
	}
}
