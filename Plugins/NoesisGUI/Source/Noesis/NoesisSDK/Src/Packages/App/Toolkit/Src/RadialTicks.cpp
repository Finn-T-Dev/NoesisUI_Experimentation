////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RadialTicks.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/DrawingContext.h>
#include <NsGui/Brushes.h>
#include <NsGui/Pen.h>

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::RadialTicks::RadialTicks()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetMinimum() const
{
    return GetValue<float>(MinimumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetMinimum(float v)
{
    SetValue<float>(MinimumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetMaximum() const
{
    return GetValue<float>(MaximumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetMaximum(float v)
{
    SetValue<float>(MaximumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetTickWidth() const
{
    return GetValue<float>(TickWidthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetTickWidth(float v)
{
    SetValue<float>(TickWidthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetTickLength() const
{
    return GetValue<float>(TickLengthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetTickLength(float v)
{
    SetValue<float>(TickLengthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetPadding() const
{
    return GetValue<float>(PaddingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetPadding(float v)
{
    SetValue<float>(PaddingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetSpacing() const
{
    return GetValue<float>(SpacingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetSpacing(float v)
{
    SetValue<float>(SpacingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Brush* NoesisApp::RadialTicks::GetBrush() const
{
    return GetValue<Noesis::Ptr<Noesis::Brush>>(BrushProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetBrush(Noesis::Brush* v)
{
    SetValue<Noesis::Ptr<Noesis::Brush>>(BrushProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetMinAngle() const
{
    return GetValue<float>(MinAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetMinAngle(float v)
{
    SetValue<float>(MinAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialTicks::GetMaxAngle() const
{
    return GetValue<float>(MaxAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::SetMaxAngle(float v)
{
    SetValue<float>(MaxAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float ValueToAngle(float v, float min, float max, float minAngle, float maxAngle)
{
    return ((Noesis::Clip(v, min, max) - min) / (max - min) * (maxAngle - minAngle)) + minAngle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialTicks::OnRender(Noesis::DrawingContext* context)
{
    Noesis::Brush* brush = GetBrush();

    float minimum = GetMinimum();
    float maximum = GetMaximum();
    float width = GetTickWidth();
    float height = GetTickLength();
    float padding = GetPadding();
    float spacing = Noesis::Max(GetSpacing(), fabsf(minimum - maximum) * 0.001f);
    float minAngle = GetMinAngle();
    float maxAngle = GetMaxAngle();

    Noesis::Ptr<Noesis::Pen> pen = Noesis::MakePtr<Noesis::Pen>();
    pen->SetBrush(brush);
    pen->SetThickness(width);

    Noesis::Size area = GetRenderSize();
    float orgX = area.width * 0.5f;
    float orgY = area.height * 0.5f;

    for (float i = minimum; i <= maximum; i += spacing)
    {
        float angle = ValueToAngle(i, minimum, maximum, minAngle, maxAngle);

        Noesis::Point p0(orgX, padding);
        Noesis::Point p1(orgX, padding + height);

        Noesis::Transform2 mtx = Noesis::Transform2::Identity();
        mtx.RotateAt(angle * Noesis::DegToRad, orgX, orgY);

        context->DrawLine(pen, p0 * mtx, p1 * mtx);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::RadialTicks, "NoesisGUIExtensions.RadialTicks")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<Noesis::StudioOrder>(2000, "Range");
    NsMeta<Noesis::StudioDesc>("Renders ticks on a radial gauge");
    NsMeta<Noesis::StudioHelpUri>("https://www.noesisengine.com/docs/App.Toolkit._RadialBorder.html");
    NsMeta<Noesis::StudioIcon>(Noesis::Uri::Pack("Toolkit", "#ToolkitIcons"), 0xE901);

    NsProp("TickWidth", &NoesisApp::RadialTicks::GetTickWidth, &NoesisApp::RadialTicks::SetTickWidth)
        .Meta<Noesis::StudioOrder>(0)
        .Meta<Noesis::StudioMin>(0.0f);
    NsProp("TickLength", &NoesisApp::RadialTicks::GetTickLength, &NoesisApp::RadialTicks::SetTickLength)
        .Meta<Noesis::StudioOrder>(1)
        .Meta<Noesis::StudioMin>(0.0f);
    NsProp("Padding", &NoesisApp::RadialTicks::GetPadding, &NoesisApp::RadialTicks::SetPadding)
        .Meta<Noesis::StudioOrder>(2)
        .Meta<Noesis::StudioMin>(0.0f);
    NsProp("Spacing", &NoesisApp::RadialTicks::GetSpacing, &NoesisApp::RadialTicks::SetSpacing)
        .Meta<Noesis::StudioOrder>(3)
        .Meta<Noesis::StudioMin>(0.0f);
    NsProp("Brush", &NoesisApp::RadialTicks::GetBrush, &NoesisApp::RadialTicks::SetBrush)
        .Meta<Noesis::StudioOrder>(4);
    NsProp("MinAngle", &NoesisApp::RadialTicks::GetMinAngle, &NoesisApp::RadialTicks::SetMinAngle)
        .Meta<Noesis::StudioOrder>(5)
        .Meta<Noesis::StudioRange>(-180.0f, 180.0f);
    NsProp("MaxAngle", &NoesisApp::RadialTicks::GetMaxAngle, &NoesisApp::RadialTicks::SetMaxAngle)
        .Meta<Noesis::StudioOrder>(6)
        .Meta<Noesis::StudioRange>(-180.0f, 180.0f);

    NsProp("Minimum", &NoesisApp::RadialTicks::GetMinimum, &NoesisApp::RadialTicks::SetMinimum)
        .Meta<Noesis::StudioOrder>(7);
    NsProp("Maximum", &NoesisApp::RadialTicks::GetMaximum, &NoesisApp::RadialTicks::SetMaximum)
        .Meta<Noesis::StudioOrder>(8);
  #endif

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    data->RegisterProperty<float>(MinimumProperty, "Minimum",
        Noesis::FrameworkPropertyMetadata::Create(0.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(MaximumProperty, "Maximum",
        Noesis::FrameworkPropertyMetadata::Create(100.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<float>(TickWidthProperty, "TickWidth",
        Noesis::FrameworkPropertyMetadata::Create(2.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(TickLengthProperty, "TickLength",
        Noesis::FrameworkPropertyMetadata::Create(6.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(PaddingProperty, "Padding",
        Noesis::FrameworkPropertyMetadata::Create(24.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(SpacingProperty, "Spacing",
        Noesis::FrameworkPropertyMetadata::Create(10.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<Noesis::Ptr<Noesis::Brush>>(BrushProperty, "Brush",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::WrapPtr(Noesis::Brushes::White()),
            Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(MinAngleProperty, "MinAngle",
        Noesis::FrameworkPropertyMetadata::Create(-120.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(MaxAngleProperty, "MaxAngle",
        Noesis::FrameworkPropertyMetadata::Create(120.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NoesisApp::RadialTicks::MinimumProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::MaximumProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::TickWidthProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::TickLengthProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::PaddingProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::SpacingProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::BrushProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::MinAngleProperty;
const Noesis::DependencyProperty* NoesisApp::RadialTicks::MaxAngleProperty;
