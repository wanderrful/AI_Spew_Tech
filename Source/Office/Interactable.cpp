#include "Interactable.h"
#include "Components/BoxComponent.h"

AInteractable::AInteractable() {
	Hitbox = CreateDefaultSubobject<UBoxComponent>(FName("Hitbox"));
	SetRootComponent(Hitbox);
	Hitbox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	Hitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	Hitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
//	Hitbox->SetCollisionProfileName(FName("BlockAll"));
	Hitbox->SetSimulatePhysics(true);
	bCanPickup = true;

}

FText AInteractable::GetDisplayText() {
	return DisplayText;
}

bool AInteractable::CanPickup() {
	return bCanPickup;
}
