////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RadialBorder.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/Brushes.h>
#include <NsGui/DrawingContext.h>
#include <NsGui/EllipseGeometry.h>
#include <NsGui/PathGeometry.h>
#include <NsGui/PathFigure.h>
#include <NsGui/ArcSegment.h>
#include <NsGui/Pen.h>

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::RadialBorder::RadialBorder()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetMinimum() const
{
    return GetValue<float>(MinimumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetMinimum(float v)
{
    SetValue<float>(MinimumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetMaximum() const
{
    return GetValue<float>(MaximumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetMaximum(float v)
{
    SetValue<float>(MaximumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetStart() const
{
    return GetValue<float>(StartProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetStart(float v)
{
    SetValue<float>(StartProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetEnd() const
{
    return GetValue<float>(EndProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetEnd(float v)
{
    SetValue<float>(EndProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetBorderWidth() const
{
    return GetValue<float>(BorderWidthProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetBorderWidth(float v)
{
    SetValue<float>(BorderWidthProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetPadding() const
{
    return GetValue<float>(PaddingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetPadding(float v)
{
    SetValue<float>(PaddingProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Brush* NoesisApp::RadialBorder::GetBrush() const
{
    return GetValue<Noesis::Ptr<Noesis::Brush>>(BrushProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetBrush(Noesis::Brush* v)
{
    SetValue<Noesis::Ptr<Noesis::Brush>>(BrushProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetMinAngle() const
{
    return GetValue<float>(MinAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetMinAngle(float v)
{
    SetValue<float>(MinAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialBorder::GetMaxAngle() const
{
    return GetValue<float>(MaxAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::SetMaxAngle(float v)
{
    SetValue<float>(MaxAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float ValueToAngle(float v, float min, float max, float minAngle, float maxAngle)
{
    return ((Noesis::Clip(v, min, max) - min) / (max - min) * (maxAngle - minAngle)) + minAngle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static Noesis::Point Rotate(float angle, float r)
{
    return Noesis::Point(sinf(Noesis::DegToRad * angle) * r, - cosf(Noesis::DegToRad * angle) * r);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialBorder::OnRender(Noesis::DrawingContext* context)
{
    Noesis::Brush* brush = GetBrush();

    float minimum = GetMinimum();
    float maximum = GetMaximum();
    float end = GetEnd();
    float start = GetStart();
    float width = GetBorderWidth();
    float padding = GetPadding();
    float minAngle = GetMinAngle();
    float maxAngle = GetMaxAngle();

    Noesis::Size area = GetRenderSize();
    float orgX = area.width * 0.5f;
    float orgY = area.height * 0.5f;

    float r = Noesis::Min(orgX, orgY) - padding - (width * 0.5f);

    if (r > 0.0f)
    {
        Noesis::Ptr<Noesis::Pen> pen = Noesis::MakePtr<Noesis::Pen>();
        pen->SetBrush(brush);
        pen->SetThickness(width);
        // StrokeEndLineCap, StrokeStartLineCap

        float angle0 = ValueToAngle(start, minimum, maximum, minAngle, maxAngle);
        float angle1 = ValueToAngle(end, minimum, maximum, minAngle, maxAngle);

        if (fabsf(angle1 - angle0) >= 360.0f)
        {
            Noesis::Ptr<Noesis::EllipseGeometry> geometry =
                Noesis::MakePtr<Noesis::EllipseGeometry>(Noesis::Point(orgX, orgY), r, r);
            context->DrawGeometry(0, pen, geometry);
        }
        else
        {
            Noesis::Ptr<Noesis::PathFigure> figure = Noesis::MakePtr<Noesis::PathFigure>();
            figure->SetStartPoint(Noesis::Point(orgX, orgY) + Rotate(angle0, r));

            Noesis::Ptr<Noesis::ArcSegment> arc = Noesis::MakePtr<Noesis::ArcSegment>();
            arc->SetSweepDirection(Noesis::SweepDirection_Clockwise);
            arc->SetIsLargeArc(angle1 - angle0 > 180.0f);
            arc->SetPoint(Noesis::Point(orgX, orgY) + Rotate(Noesis::Min(angle1, maxAngle), r));
            arc->SetSize(Noesis::Size(r, r));

            figure->GetSegments()->Add(arc);

            Noesis::Ptr<Noesis::PathGeometry> geometry = Noesis::MakePtr<Noesis::PathGeometry>();
            geometry->GetFigures()->Add(figure);
            context->DrawGeometry(0, pen, geometry);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::RadialBorder, "NoesisGUIExtensions.RadialBorder")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<Noesis::StudioOrder>(2000, "Range");
    NsMeta<Noesis::StudioDesc>("Radial helper for drawing radial borders");
    NsMeta<Noesis::StudioHelpUri>("https://www.noesisengine.com/docs/App.Toolkit._RadialBorder.html");
    NsMeta<Noesis::StudioIcon>(Noesis::Uri::Pack("Toolkit", "#ToolkitIcons"), 0xE904);

    NsProp("Start", &NoesisApp::RadialBorder::GetStart, &NoesisApp::RadialBorder::SetStart)
        .Meta<Noesis::StudioOrder>(0);
    NsProp("End", &NoesisApp::RadialBorder::GetEnd, &NoesisApp::RadialBorder::SetEnd)
        .Meta<Noesis::StudioOrder>(1);

    NsProp("BorderWidth", &NoesisApp::RadialBorder::GetBorderWidth, &NoesisApp::RadialBorder::SetBorderWidth)
        .Meta<Noesis::StudioOrder>(2)
        .Meta<Noesis::StudioMin>(0.0f);
    NsProp("Padding", &NoesisApp::RadialBorder::GetPadding, &NoesisApp::RadialBorder::SetPadding)
        .Meta<Noesis::StudioOrder>(3)
        .Meta<Noesis::StudioMin>(0.0f);

    NsProp("Brush", &NoesisApp::RadialBorder::GetBrush, &NoesisApp::RadialBorder::SetBrush)
        .Meta<Noesis::StudioOrder>(4);

    NsProp("MinAngle", &NoesisApp::RadialBorder::GetMinAngle, &NoesisApp::RadialBorder::SetMinAngle)
        .Meta<Noesis::StudioOrder>(5)
        .Meta<Noesis::StudioRange>(-180.0f, 180.0f);
    NsProp("MaxAngle", &NoesisApp::RadialBorder::GetMaxAngle, &NoesisApp::RadialBorder::SetMaxAngle)
        .Meta<Noesis::StudioOrder>(6)
        .Meta<Noesis::StudioRange>(-180.0f, 180.0f);

    NsProp("Minimum", &NoesisApp::RadialBorder::GetMinimum, &NoesisApp::RadialBorder::SetMinimum)
        .Meta<Noesis::StudioOrder>(7);
    NsProp("Maximum", &NoesisApp::RadialBorder::GetMaximum, &NoesisApp::RadialBorder::SetMaximum)
        .Meta<Noesis::StudioOrder>(8);
  #endif

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    data->RegisterProperty<float>(MinimumProperty, "Minimum",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(MaximumProperty, "Maximum",
        Noesis::FrameworkPropertyMetadata::Create(100.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(StartProperty, "Start",
        Noesis::FrameworkPropertyMetadata::Create(0.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(EndProperty, "End",
        Noesis::FrameworkPropertyMetadata::Create(100.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<float>(BorderWidthProperty, "BorderWidth",
        Noesis::FrameworkPropertyMetadata::Create(2.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(PaddingProperty, "Padding",
        Noesis::FrameworkPropertyMetadata::Create(24.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<Noesis::Ptr<Noesis::Brush>>(BrushProperty, "Brush",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::WrapPtr(Noesis::Brushes::White()),
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));

    data->RegisterProperty<float>(MinAngleProperty, "MinAngle",
        Noesis::FrameworkPropertyMetadata::Create(-120.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(MaxAngleProperty, "MaxAngle",
        Noesis::FrameworkPropertyMetadata::Create(120.0f, Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NoesisApp::RadialBorder::MinimumProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::MaximumProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::StartProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::EndProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::BorderWidthProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::PaddingProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::BrushProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::MinAngleProperty;
const Noesis::DependencyProperty* NoesisApp::RadialBorder::MaxAngleProperty;
