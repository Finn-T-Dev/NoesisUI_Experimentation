////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "NineSliceImage.h"

#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/ImageSource.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsDrawing/Thickness.h>

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::ImageSource* NoesisApp::NineSliceImage::GetImageSource() const
{
    return GetValue<Noesis::Ptr<Noesis::ImageSource>>(ImageSourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::NineSliceImage::SetImageSource(Noesis::ImageSource* value)
{
    SetValue<Noesis::Ptr<Noesis::ImageSource>>(ImageSourceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Thickness& NoesisApp::NineSliceImage::GetSlices() const
{
    return GetValue<Noesis::Thickness>(SlicesProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::NineSliceImage::SetSlices(const Noesis::Thickness& value)
{
    SetValue<Noesis::Thickness>(SlicesProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void UpdateSlices(NoesisApp::NineSliceImage* image)
{
    float width = 0;
    float height = 0;

    Noesis::ImageSource* imageSource = image->GetImageSource();
    if (imageSource != nullptr)
    {
        width = imageSource->GetWidth();
        height = imageSource->GetHeight();
    }

    const Noesis::Thickness& slices = image->GetSlices();

    float wl = slices.left;
    float wc = width - slices.left - slices.right;
    float wr = slices.right;
    float ht = slices.top;
    float hc = height - slices.top - slices.bottom;
    float hb = slices.bottom;

    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::TopLeftViewboxProperty, Noesis::Rect(0.0f, 0.0f, wl, ht));
    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::TopCenterViewboxProperty, Noesis::Rect(wl, 0.0f, wl + wc, ht));
    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::TopRightViewboxProperty, Noesis::Rect(wl + wc, 0.0f, wl + wc + wr, ht));

    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::CenterLeftViewboxProperty, Noesis::Rect(0.0f, ht, wl, ht + hc));
    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::CenterViewboxProperty, Noesis::Rect(wl, ht, wl + wc, ht + hc));
    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::CenterRightViewboxProperty, Noesis::Rect(wl + wc, ht, wl + wc + wr, ht + hc));

    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::BottomLeftViewboxProperty, Noesis::Rect(0.0f, ht + hc, wl, ht + hc + hb));
    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::BottomCenterViewboxProperty, Noesis::Rect(wl, ht + hc, wl + wc, ht + hc + hb));
    image->SetValue<Noesis::Rect>(NoesisApp::NineSliceImage::BottomRightViewboxProperty, Noesis::Rect(wl + wc, ht + hc, wl + wc + wr, ht + hc + hb));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::NineSliceImage, "NoesisGUIExtensions.NineSliceImage")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<Noesis::StudioOrder>(2000, "Media");
    NsMeta<Noesis::StudioDesc>("Renders scalable images while preserving corner integrity during resizing");
    NsMeta<Noesis::StudioIcon>(Noesis::Uri::Pack("Toolkit", "#ToolkitIcons"), 0xE908);

    NsProp("ImageSource", &NoesisApp::NineSliceImage::GetImageSource, &NoesisApp::NineSliceImage::SetImageSource)
        .Meta<Noesis::StudioOrder>(500);
    NsProp("Slices", &NoesisApp::NineSliceImage::GetSlices, &NoesisApp::NineSliceImage::SetSlices)
        .Meta<Noesis::StudioOrder>(501);

    NsProp("TopLeftViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("TopCenterViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("TopRightViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("CenterLeftViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("CenterViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("CenterRightViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("BottomLeftViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("BottomCenterViewbox")
        .Meta<Noesis::StudioOrder>(-1);
    NsProp("BottomRightViewbox")
        .Meta<Noesis::StudioOrder>(-1);
  #endif

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    data->OverrideMetadata<const Noesis::Type*>(FrameworkElement::DefaultStyleKeyProperty,
        "DefaultStyleKey", Noesis::FrameworkPropertyMetadata::Create<const Noesis::Type*>(
        Noesis::TypeOf<NineSliceImage>()));

    auto OnSourceChanged = [](DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs&)
    {
        NineSliceImage* image = (NineSliceImage*)d;
        image->CoerceValue<Noesis::Thickness>(SlicesProperty);
        UpdateSlices(image);
    };

    data->RegisterProperty<Noesis::Ptr<Noesis::ImageSource>>(ImageSourceProperty, "ImageSource",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::ImageSource>(), OnSourceChanged));

    auto OnSlicesChanged = [](DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs&)
    {
        UpdateSlices((NineSliceImage*)d);
    };

    auto CoerceSlices = [](const DependencyObject* d, const void* value, void* coercedValue)
    {
        NineSliceImage* image = (NineSliceImage*)d;

        float width = 0;
        float height = 0;

        Noesis::ImageSource* imageSource = image->GetImageSource();
        if (imageSource != nullptr)
        {
            width = imageSource->GetWidth();
            height = imageSource->GetHeight();
        }

        const Noesis::Thickness& slices = *(Noesis::Thickness*)(value);
        Noesis::Thickness& coerced = *(Noesis::Thickness*)(coercedValue);

        coerced.left = Noesis::Clip(slices.left, 0.0f, width);
        coerced.right = Noesis::Clip(slices.right, 0.0f, width - coerced.left);
        coerced.top = Noesis::Clip(slices.top, 0.0f, height);
        coerced.bottom = Noesis::Clip(slices.bottom, 0.0f, height - coerced.top);

        return true;
    };

    data->RegisterProperty<Noesis::Thickness>(SlicesProperty, "Slices",
        Noesis::PropertyMetadata::Create(Noesis::Thickness(), OnSlicesChanged, CoerceSlices));

    data->RegisterProperty<Noesis::Rect>(TopLeftViewboxProperty, "TopLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(TopCenterViewboxProperty, "TopCenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(TopRightViewboxProperty, "TopRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(CenterLeftViewboxProperty, "CenterLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(CenterViewboxProperty, "CenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(CenterRightViewboxProperty, "CenterRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(BottomLeftViewboxProperty, "BottomLeftViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(BottomCenterViewboxProperty, "BottomCenterViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
    data->RegisterProperty<Noesis::Rect>(BottomRightViewboxProperty, "BottomRightViewbox",
        Noesis::PropertyMetadata::Create(Noesis::Rect()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::ImageSourceProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::SlicesProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::TopLeftViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::TopCenterViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::TopRightViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::CenterLeftViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::CenterViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::CenterRightViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::BottomLeftViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::BottomCenterViewboxProperty;
const Noesis::DependencyProperty* NoesisApp::NineSliceImage::BottomRightViewboxProperty;
