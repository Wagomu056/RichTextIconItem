// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "Fonts/SlateFontInfo.h"
#include "RichTextIconItemDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RICHTEXTICONITEM_API URichTextIconItemDecorator : public URichTextBlockImageDecorator
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;

	FSlateFontInfo GetFont() const { return Font; }
	int32 GetHeight() const { return Height; }

protected:
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, Category = Appearance)
	int32 Height;

};
