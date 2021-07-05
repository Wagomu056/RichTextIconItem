// Fill out your copyright notice in the Description page of Project Settings.


#include "RichTextIconItemDecorator.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"

class SIconItem : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SIconItem)
	{}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const FSlateBrush* Brush, const FSlateFontInfo& FontInfo, const FText& Content, int32 Height)
	{
		if (ensure(Brush))
		{
			float BoxHeight = Height;

			ChildSlot
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(10.0f)
				[
					SNew(SBox)
					.WidthOverride(BoxHeight)
				.HeightOverride(BoxHeight)
				[
					SNew(SImage)
					.Image(Brush)
				]
				]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(10.0f)
				.VAlign(EVerticalAlignment::VAlign_Center)
				[
					SNew(STextBlock)
					.Text(Content)
				.Font(FontInfo)
				.ColorAndOpacity(FSlateColor(FLinearColor::White))
				]
				];
		}
	}
};

class FRichIconItem : public FRichTextDecorator
{
public:
	FRichIconItem(URichTextBlock* InOwner, URichTextIconItemDecorator* InDecorator)
		: FRichTextDecorator(InOwner)
		, Decorator(InDecorator)
	{
	}

	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override
	{
		if (RunParseResult.Name == TEXT("IconItem") && RunParseResult.MetaData.Contains(TEXT("id")))
		{
			const FTextRange& IdRange = RunParseResult.MetaData[TEXT("id")];
			const FString TagId = Text.Mid(IdRange.BeginIndex, IdRange.EndIndex - IdRange.BeginIndex);

			const bool bWarnIfMissing = false;
			return Decorator->FindImageBrush(*TagId, bWarnIfMissing) != nullptr;
		}

		return false;
	}

protected:
	virtual TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& TextStyle) const override
	{
		const bool bWarnIfMissing = true;
		const FSlateBrush* Brush = Decorator->FindImageBrush(*RunInfo.MetaData[TEXT("id")], bWarnIfMissing);

		return SNew(SIconItem, Brush, Decorator->GetFont(), RunInfo.Content, Decorator->GetHeight());
	}

private:
	URichTextIconItemDecorator* Decorator;
};

TSharedPtr<ITextDecorator> URichTextIconItemDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FRichIconItem(InOwner, this));
}

