////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RadialGauge.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/SolidColorBrush.h>

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
RadialGauge::RadialGauge()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetScaleWidth() const
{
    return DependencyObject::GetValue<float>(ScaleWidthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetScaleWidth(float v)
{
    DependencyObject::SetValue<float>(ScaleWidthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SolidColorBrush* RadialGauge::GetScaleBrush() const
{
    return DependencyObject::GetValue<Ptr<SolidColorBrush>>(ScaleBrushProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetScaleBrush(SolidColorBrush* v)
{
    DependencyObject::SetValue<Ptr<SolidColorBrush>>(ScaleBrushProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetScalePadding() const
{
    return DependencyObject::GetValue<float>(ScalePaddingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetScalePadding(float v)
{
    DependencyObject::SetValue<float>(ScalePaddingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SolidColorBrush* RadialGauge::GetNeedleBrush() const
{
    return DependencyObject::GetValue<Ptr<SolidColorBrush>>(NeedleBrushProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetNeedleBrush(SolidColorBrush* v)
{
    DependencyObject::SetValue<Ptr<SolidColorBrush>>(NeedleBrushProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetNeedleLength() const
{
    return DependencyObject::GetValue<float>(NeedleLengthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetNeedleLength(float v)
{
    DependencyObject::SetValue<float>(NeedleLengthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetNeedleWidth() const
{
    return DependencyObject::GetValue<float>(NeedleWidthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetNeedleWidth(float v)
{
    DependencyObject::SetValue<float>(NeedleWidthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SolidColorBrush* RadialGauge::GetTrailBrush() const
{
    return DependencyObject::GetValue<Ptr<SolidColorBrush>>(TrailBrushProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetTrailBrush(SolidColorBrush* v)
{
    DependencyObject::SetValue<Ptr<SolidColorBrush>>(TrailBrushProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::SolidColorBrush* RadialGauge::GetTickBrush() const
{
    return DependencyObject::GetValue<Ptr<SolidColorBrush>>(TickBrushProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetTickBrush(Noesis::SolidColorBrush* v)
{
    DependencyObject::SetValue<Ptr<SolidColorBrush>>(TickBrushProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetTickPadding() const
{
    return DependencyObject::GetValue<float>(TickPaddingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetTickPadding(float v)
{
    DependencyObject::SetValue<float>(TickPaddingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetTickWidth() const
{
    return DependencyObject::GetValue<float>(TickWidthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetTickWidth(float v)
{
    DependencyObject::SetValue<float>(TickWidthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetTickLength() const
{
    return DependencyObject::GetValue<float>(TickLengthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetTickLength(float v)
{
    DependencyObject::SetValue<float>(TickLengthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetTickSpacing() const
{
    return DependencyObject::GetValue<float>(TickSpacingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetTickSpacing(float v)
{
    DependencyObject::SetValue<float>(TickSpacingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetMinAngle() const
{
    return DependencyObject::GetValue<float>(MinAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetMinAngle(float v)
{
    DependencyObject::SetValue<float>(MinAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialGauge::GetMaxAngle() const
{
    return DependencyObject::GetValue<float>(MaxAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialGauge::SetMaxAngle(float v)
{
    DependencyObject::SetValue<float>(MaxAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(RadialGauge, "NoesisGUIExtensions.RadialGauge")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<StudioOrder>(2000, "Range");
    NsMeta<StudioDesc>("Represents a radial gauge with customizable elements such as needle, ticks, and border");
    NsMeta<StudioHelpUri>("https://www.noesisengine.com/docs/App.Toolkit._RadialBorder.html");
    NsMeta<StudioIcon>(Uri::Pack("Toolkit", "#ToolkitIcons"), 0xE900);

    NsProp("ScaleWidth", &RadialGauge::GetScaleWidth, &RadialGauge::SetScaleWidth)
        .Meta<StudioOrder>(0)
        .Meta<StudioMin>(0.0f);
    NsProp("ScalePadding", &RadialGauge::GetScalePadding, &RadialGauge::SetScalePadding)
        .Meta<StudioOrder>(1)
        .Meta<StudioMin>(0.0f);
    NsProp("ScaleBrush", &RadialGauge::GetScaleBrush, &RadialGauge::SetScaleBrush)
        .Meta<StudioOrder>(2);

    NsProp("TickWidth", &RadialGauge::GetTickWidth, &RadialGauge::SetTickWidth)
        .Meta<StudioOrder>(3)
        .Meta<StudioMin>(0.0f);
    NsProp("TickLength", &RadialGauge::GetTickLength, &RadialGauge::SetTickLength)
        .Meta<StudioOrder>(4)
        .Meta<StudioMin>(0.0f);
    NsProp("TickPadding", &RadialGauge::GetTickPadding, &RadialGauge::SetTickPadding)
        .Meta<StudioOrder>(5)
        .Meta<StudioMin>(0.0f);
    NsProp("TickSpacing", &RadialGauge::GetTickSpacing, &RadialGauge::SetTickSpacing)
        .Meta<StudioOrder>(6)
        .Meta<StudioMin>(0.0f);
    NsProp("TickBrush", &RadialGauge::GetTickBrush, &RadialGauge::SetTickBrush)
        .Meta<StudioOrder>(7);

    NsProp("NeedleWidth", &RadialGauge::GetNeedleWidth, &RadialGauge::SetNeedleWidth)
        .Meta<StudioOrder>(8)
        .Meta<StudioMin>(0.0f);
    NsProp("NeedleLength", &RadialGauge::GetNeedleLength, &RadialGauge::SetNeedleLength)
        .Meta<StudioOrder>(9)
        .Meta<StudioMin>(0.0f);
    NsProp("NeedleBrush", &RadialGauge::GetNeedleBrush, &RadialGauge::SetNeedleBrush)
        .Meta<StudioOrder>(10);
    NsProp("TrailBrush", &RadialGauge::GetTrailBrush, &RadialGauge::SetTrailBrush)
        .Meta<StudioOrder>(11);

    NsProp("MinAngle", &RadialGauge::GetMinAngle, &RadialGauge::SetMinAngle)
        .Meta<StudioOrder>(12)
        .Meta<StudioRange>(-180.0f, 180.0f);
    NsProp("MaxAngle", &RadialGauge::GetMaxAngle, &RadialGauge::SetMaxAngle)
        .Meta<StudioOrder>(13)
        .Meta<StudioRange>(-180.0f, 180.0f);
  #endif

    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->OverrideMetadata<const Type*>(FrameworkElement::DefaultStyleKeyProperty,
        "DefaultStyleKey", FrameworkPropertyMetadata::Create<const Type*>(TypeOf<RadialGauge>()));

    data->RegisterProperty<float>(MinAngleProperty, "MinAngle",
        FrameworkPropertyMetadata::Create(-150.0f));
    data->RegisterProperty<float>(MaxAngleProperty, "MaxAngle",
        FrameworkPropertyMetadata::Create(150.0f));

    data->RegisterProperty<float>(ScaleWidthProperty, "ScaleWidth",
        FrameworkPropertyMetadata::Create(12.0f));
    data->RegisterProperty<Ptr<Brush>>(ScaleBrushProperty, "ScaleBrush",
        FrameworkPropertyMetadata::Create(Ptr<Brush>()));
    data->RegisterProperty<float>(ScalePaddingProperty, "ScalePadding",
        FrameworkPropertyMetadata::Create(0.0f));

    data->RegisterProperty<float>(TickWidthProperty, "TickWidth",
        FrameworkPropertyMetadata::Create(2.0f));
    data->RegisterProperty<float>(TickLengthProperty, "TickLength",
        FrameworkPropertyMetadata::Create(6.0f));
    data->RegisterProperty<float>(TickPaddingProperty, "TickPadding",
        FrameworkPropertyMetadata::Create(24.0f));
    data->RegisterProperty<float>(TickSpacingProperty, "TickSpacing",
        FrameworkPropertyMetadata::Create(15.0f));
    data->RegisterProperty<Ptr<SolidColorBrush>>(TickBrushProperty, "TickBrush",
        FrameworkPropertyMetadata::Create(Ptr<SolidColorBrush>()));

    data->RegisterProperty<Ptr<SolidColorBrush>>(NeedleBrushProperty, "NeedleBrush",
        FrameworkPropertyMetadata::Create(Ptr<SolidColorBrush>()));
    data->RegisterProperty<float>(NeedleLengthProperty, "NeedleLength",
        FrameworkPropertyMetadata::Create(58.0f));
    data->RegisterProperty<float>(NeedleWidthProperty, "NeedleWidth",
        FrameworkPropertyMetadata::Create(5.0f));

    data->RegisterProperty<Ptr<Brush>>(TrailBrushProperty, "TrailBrush",
        FrameworkPropertyMetadata::Create(Ptr<Brush>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* RadialGauge::ScaleWidthProperty;
const DependencyProperty* RadialGauge::ScaleBrushProperty;
const DependencyProperty* RadialGauge::ScalePaddingProperty;
const DependencyProperty* RadialGauge::NeedleBrushProperty;
const DependencyProperty* RadialGauge::NeedleLengthProperty;
const DependencyProperty* RadialGauge::NeedleWidthProperty;
const DependencyProperty* RadialGauge::TrailBrushProperty;
const DependencyProperty* RadialGauge::TickBrushProperty;
const DependencyProperty* RadialGauge::TickSpacingProperty;
const DependencyProperty* RadialGauge::TickWidthProperty;
const DependencyProperty* RadialGauge::TickLengthProperty;
const DependencyProperty* RadialGauge::TickPaddingProperty;
const DependencyProperty* RadialGauge::MinAngleProperty;
const DependencyProperty* RadialGauge::MaxAngleProperty;
