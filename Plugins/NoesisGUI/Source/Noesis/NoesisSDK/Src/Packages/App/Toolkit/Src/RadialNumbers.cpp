////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RadialNumbers.h>
#include <NsCore/StringFormat.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/FormattedText.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/Brushes.h>
#include <NsGui/MatrixTransform.h>
#include <NsGui/DrawingContext.h>
#include <NsGui/FontFamily.h>
#include <NsGui/Pen.h>

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
RadialNumbers::RadialNumbers()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialNumbers::GetMinimum() const
{
    return GetValue<float>(MinimumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetMinimum(float v)
{
    SetValue<float>(MinimumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialNumbers::GetMaximum() const
{
    return GetValue<float>(MaximumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetMaximum(float v)
{
    SetValue<float>(MaximumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialNumbers::GetPadding() const
{
    return GetValue<float>(PaddingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetPadding(float v)
{
    SetValue<float>(PaddingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialNumbers::GetSpacing() const
{
    return GetValue<float>(SpacingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetSpacing(float v)
{
    SetValue<float>(SpacingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Brush* RadialNumbers::GetBrush() const
{
    return GetValue<Ptr<Brush>>(BrushProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetBrush(Brush* v)
{
    SetValue<Ptr<Brush>>(BrushProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
FontFamily* RadialNumbers::GetFontFamily() const
{
    return GetValue<Ptr<FontFamily>>(FontFamilyProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetFontFamily(Noesis::FontFamily* v)
{
    SetValue<Ptr<FontFamily>>(FontFamilyProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialNumbers::GetFontSize() const
{
    return GetValue<float>(FontSizeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetFontSize(float v)
{
    SetValue<float>(FontSizeProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialNumbers::GetMinAngle() const
{
    return GetValue<float>(MinAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetMinAngle(float v)
{
    SetValue<float>(MinAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float RadialNumbers::GetMaxAngle() const
{
    return GetValue<float>(MaxAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetMaxAngle(float v)
{
    SetValue<float>(MaxAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool RadialNumbers::GetRotated() const
{
    return GetValue<bool>(RotatedProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::SetRotated(bool v)
{
    SetValue<bool>(RotatedProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float ValueToAngle(float v, float min, float max, float minAngle, float maxAngle)
{
    return ((Clip(v, min, max) - min) / (max - min) * (maxAngle - minAngle)) + minAngle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadialNumbers::OnRender(Noesis::DrawingContext* context)
{
    FontFamily* font = GetFontFamily();
    float minimum = GetMinimum();
    float maximum = GetMaximum();
    float padding = GetPadding();
    float spacing = Max(GetSpacing(), fabsf(minimum - maximum) * 0.001f);
    float fontSize = GetFontSize();
    float minAngle = GetMinAngle();
    float maxAngle = GetMaxAngle();
    bool rotated = GetRotated();
    Brush* brush = GetBrush();

    Size area = GetRenderSize();
    float orgX = area.width * 0.5f;
    float orgY = area.height * 0.5f;

    for (float i = minimum; i <= maximum; i += spacing)
    {
        float angle = ValueToAngle(i, minimum, maximum, minAngle, maxAngle);

        String str;
        StringFormat(i, str);

        Ptr<FormattedText> text = MakePtr<FormattedText>(str.Str(), font, fontSize, brush);
        Rect rect = text->GetBounds();

        if (rotated)
        {
            Transform2 mtx = Transform2::Identity();
            mtx = PreTrans(orgX - rect.width * 0.5f, padding - rect.height * 0.5f, mtx);
            mtx.RotateAt(angle * DegToRad, orgX, orgY);

            context->PushTransform(MakePtr<MatrixTransform>(mtx));
            context->DrawText(text, rect);
            context->Pop();
        }
        else
        {
            Transform2 mtx = Transform2::Identity();
            mtx.RotateAt(angle * DegToRad, orgX, orgY);

            Point o = Point(orgX, padding) * mtx;
            rect.x = o.x - rect.width * 0.5f;
            rect.y = o.y - rect.height * 0.5f;

            context->DrawText(text, rect);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(RadialNumbers, "NoesisGUIExtensions.RadialNumbers")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<StudioOrder>(2000, "Range");
    NsMeta<StudioDesc>("Renders the numerical labels on a radial gauge");
    NsMeta<StudioHelpUri>("https://www.noesisengine.com/docs/App.Toolkit._RadialBorder.html");
    NsMeta<StudioIcon>(Uri::Pack("Toolkit", "#ToolkitIcons"), 0xE902);

    NsProp("Padding", &RadialNumbers::GetPadding, &RadialNumbers::SetPadding)
        .Meta<StudioOrder>(0)
        .Meta<StudioMin>(0.0f);
    NsProp("Spacing", &RadialNumbers::GetSpacing, &RadialNumbers::SetSpacing)
        .Meta<StudioOrder>(1)
        .Meta<StudioMin>(0.0f);

    NsProp("Brush", &RadialNumbers::GetBrush, &RadialNumbers::SetBrush)
        .Meta<StudioOrder>(2);

    NsProp("FontFamily", &RadialNumbers::GetFontFamily, &RadialNumbers::SetFontFamily)
        .Meta<StudioOrder>(3);
    NsProp("FontSize", &RadialNumbers::GetFontSize, &RadialNumbers::SetFontSize)
        .Meta<StudioOrder>(4);

    NsProp("MinAngle", &RadialNumbers::GetMinAngle, &RadialNumbers::SetMinAngle)
        .Meta<StudioOrder>(5)
        .Meta<StudioRange>(-180.0f, 180.0f);
    NsProp("MaxAngle", &RadialNumbers::GetMaxAngle, &RadialNumbers::SetMaxAngle)
        .Meta<StudioOrder>(6)
        .Meta<StudioRange>(-180.0f, 180.0f);

    NsProp("Minimum", &RadialNumbers::GetMinimum, &RadialNumbers::SetMinimum)
        .Meta<StudioOrder>(7);
    NsProp("Maximum", &RadialNumbers::GetMaximum, &RadialNumbers::SetMaximum)
        .Meta<StudioOrder>(8);

    NsProp("Rotated", &RadialNumbers::GetRotated, &RadialNumbers::SetRotated)
        .Meta<StudioOrder>(9);
  #endif

    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());

    data->RegisterProperty<float>(MinimumProperty, "Minimum",
        FrameworkPropertyMetadata::Create(0.0f, FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(MaximumProperty, "Maximum",
        FrameworkPropertyMetadata::Create(100.0f, FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<float>(PaddingProperty, "Padding",
        FrameworkPropertyMetadata::Create(24.0f, FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(SpacingProperty, "Spacing",
        FrameworkPropertyMetadata::Create(10.0f, FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<Ptr<Brush>>(BrushProperty, "Brush",
        FrameworkPropertyMetadata::Create(WrapPtr(Brushes::White()),
        FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<Ptr<FontFamily>>(FontFamilyProperty, "FontFamily",
        FrameworkPropertyMetadata::Create(MakePtr<FontFamily>(),
        FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(FontSizeProperty, "FontSize",
        FrameworkPropertyMetadata::Create(28.0f, FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<float>(MinAngleProperty, "MinAngle",
        FrameworkPropertyMetadata::Create(-120.0f, FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(MaxAngleProperty, "MaxAngle",
        FrameworkPropertyMetadata::Create(120.0f, FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<bool>(RotatedProperty, "Rotated",
        FrameworkPropertyMetadata::Create(false, FrameworkPropertyMetadataOptions_AffectsRender));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* RadialNumbers::MinimumProperty;
const DependencyProperty* RadialNumbers::MaximumProperty;
const DependencyProperty* RadialNumbers::PaddingProperty;
const DependencyProperty* RadialNumbers::SpacingProperty;
const DependencyProperty* RadialNumbers::BrushProperty;
const DependencyProperty* RadialNumbers::FontFamilyProperty;
const DependencyProperty* RadialNumbers::FontSizeProperty;
const DependencyProperty* RadialNumbers::MinAngleProperty;
const DependencyProperty* RadialNumbers::MaxAngleProperty;
const DependencyProperty* RadialNumbers::RotatedProperty;
