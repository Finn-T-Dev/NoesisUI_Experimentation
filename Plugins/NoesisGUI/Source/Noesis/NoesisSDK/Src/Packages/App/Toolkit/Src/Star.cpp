////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/Star.h>
#include <NsGui/UIElementData.h>
#include <NsGui/StreamGeometry.h>
#include <NsGui/StreamGeometryContext.h>
#include <NsGui/DrawingContext.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsCore/ReflectionImplement.h>

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
static void GetArcPoints(const Noesis::Vector2& p0, const Noesis::Vector2& p1,
    const Noesis::Vector2& p2, float radius, Noesis::Vector2& anchor0, Noesis::Vector2& anchor1,
    bool& ccw)
{
    // Given the corner defined by points P0, P1, and P2, this function returns the anchor points
    // where the arc with the specified radius should start and end to round the corner

    //  p0     anchor0   p1
    //  .-------x--------.
    //                   |
    //                   |
    //                   x anchor1
    //                   |
    //                   |
    //                   .
    //                   p2

    NS_ASSERT(radius >= 0.01f);

    Noesis::Vector2 d0 = p0 - p1;
    float l0 = Length(d0);
    NS_ASSERT(!Noesis::IsZero(l0));
    d0 /= l0;

    Noesis::Vector2 d1 = p2 - p1;
    float l1 = Length(d1);
    NS_ASSERT(!Noesis::IsZero(l1));
    d1 /= l1;

    float angle = SignedAngle(d0, d1);
    float dist = Noesis::Min(Noesis::Min(radius / tanf(fabsf(angle) * 0.5f), l0), l1);

    anchor0 = p1 + d0 * dist;
    anchor1 = p1 + d1 * dist;
    ccw = angle > 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void BuildGeometry(Noesis::StreamGeometry* geo, Noesis::Rect rect, float ratio, float radius,
    uint32_t count)
{
    // Sanitize input values
    radius = Noesis::Max(radius, 0.0f);
    count = Noesis::Clip(count, 3U, 60U);
    ratio = Noesis::Clip(ratio, 0.0f, 1.0f);

    bool rounded = radius > 0.01f;
    float outRadius = rect.height * 0.5f;
    float inRadius = outRadius * ratio;

    Noesis::Transform2 rot = Noesis::Transform2::Rot(Noesis::TwoPi / count);
    Noesis::Transform2 mtx = Noesis::Transform2::Trans(outRadius + rect.x, outRadius + rect.y) *
        Noesis::Transform2::Scale(rect.width / rect.height, 1.0);

    Noesis::Vector2 r0 = Noesis::Vector2(0.0f, -inRadius)
        * Noesis::Transform2::Rot(-Noesis::TwoPi / (2.0f * count));
    Noesis::Vector2 r1(0.0f, -outRadius);

    Noesis::StreamGeometryContext ctx = geo->Open();

    if (rounded)
    {
        bool ccw;
        Noesis::Vector2 a0, a1;
        GetArcPoints(r0 * mtx, r1 * mtx, r0 * rot * mtx, radius, a0, a1, ccw);

        ctx.BeginFigure(a0, true);

        for (uint32_t i = 0; i < count; i++)
        {
            ctx.ArcTo(a1, Noesis::Size(radius, radius), 0.0f, false,
                Noesis::SweepDirection_Clockwise);

            Noesis::Vector2 a1_ = a1;
            r0 = r0 * rot;
            GetArcPoints(r1 * mtx, r0 * mtx, r1 * rot * mtx, radius, a0, a1, ccw);

            if (Length((r1 * mtx) - a0) > Length((r1 * mtx) - a1_))
            {
                ctx.LineTo(a0);
            }

            Noesis::SweepDirection dir = ccw ? Noesis::SweepDirection_Counterclockwise
                : Noesis::SweepDirection_Clockwise;

            a1_ = a1;
            r1 = r1 * rot;
            GetArcPoints(r0 * mtx, r1 * mtx, r0 * rot * mtx, radius, a0, a1, ccw);

            if (Length((r0 * mtx) - a0) < Length((r0 * mtx) - a1_))
            {
                ctx.ArcTo(a0, Noesis::Size(radius, radius), 0.0f, false, dir);
            }
            else
            {
                ctx.ArcTo(a1_, Noesis::Size(radius, radius), 0.0f, false, dir);
                ctx.LineTo(a0);
            }
        }
    }
    else
    {
        ctx.BeginFigure(r1 * mtx, true);

        for (uint32_t i = 0; i < count; i++)
        {
            r0 = r0 * rot;
            ctx.LineTo(r0 * mtx);

            r1 = r1 * rot;
            ctx.LineTo(r1 * mtx);
        }
    }

    ctx.Close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::Star::Star(): mRenderGeometry(Noesis::MakePtr<Noesis::StreamGeometry>())
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::Star::~Star()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::Star::GetRatio() const
{
    return GetValue<float>(RatioProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::Star::SetRatio(float v)
{
    SetValue<float>(RatioProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t NoesisApp::Star::GetCount() const
{
    return GetValue<uint32_t>(CountProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::Star::SetCount(uint32_t v)
{
    SetValue<uint32_t>(CountProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::Star::GetRadius() const
{
    return GetValue<float>(RadiusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::Star::SetRadius(float v)
{
    SetValue<float>(RadiusProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::Star::OnRender(Noesis::DrawingContext* context)
{
    BuildGeometry(mRenderGeometry, mRect, GetRatio(), GetRadius(), GetCount());
    context->DrawGeometry(GetFill(), GetPen(), mRenderGeometry);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size NoesisApp::Star::MeasureOverride(const Noesis::Size& availableSize)
{
    auto GetMinimumSize = [this]() -> Noesis::Size
    {
        float strokeThickness = GetValidStrokeThickness();
        return Noesis::Size(strokeThickness, strokeThickness);
    };

    if (GetStretch() != Noesis::Stretch_UniformToFill)
    {
        return GetMinimumSize();
    }

    if (Noesis::IsInfinity(availableSize.width))
    {
        if (Noesis::IsInfinity(availableSize.height))
        {
            return GetMinimumSize();
        }
        else
        {
            return Noesis::Size(availableSize.height, availableSize.height);
        }
    }
    else
    {
        if (Noesis::IsInfinity(availableSize.height))
        {
            return Noesis::Size(availableSize.width, availableSize.width);
        }
        else
        {
            float maxSize = Noesis::Max(availableSize.width, availableSize.height);
            return Noesis::Size(maxSize, maxSize);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size NoesisApp::Star::ArrangeOverride(const Noesis::Size& finalSize)
{
    mRect = GetFinalBounds(finalSize);
    return finalSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Geometry* NoesisApp::Star::GetRenderGeometry() const
{
    return mRenderGeometry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::Star, "NoesisGUIExtensions.Star")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<Noesis::StudioOrder>(2000, "Shape");
    NsMeta<Noesis::StudioDesc>("Renders a star shape with variable number of points");
    NsMeta<Noesis::StudioHelpUri>("https://www.noesisengine.com/docs/App.Toolkit._Star.html");
    NsMeta<Noesis::StudioIcon>(Noesis::Uri::Pack("Toolkit", "#ToolkitIcons"), 0xE906);

    NsProp("Count", &Star::GetCount, &Star::SetCount)
        .Meta<Noesis::StudioOrder>(0);
    NsProp("Ratio", &Star::GetRatio, &Star::SetRatio)
        .Meta<Noesis::StudioOrder>(1)
        .Meta<Noesis::StudioRange>(0.0f, 1.0f);
    NsProp("Radius", &Star::GetRadius, &Star::SetRadius)
        .Meta<Noesis::StudioOrder>(2)
        .Meta<Noesis::StudioMin>(0.0f);
  #endif

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    data->RegisterProperty<float>(RatioProperty, "Ratio",
        Noesis::FrameworkPropertyMetadata::Create(0.382f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<uint32_t>(CountProperty, "Count",
        Noesis::FrameworkPropertyMetadata::Create(5U,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    data->RegisterProperty<float>(RadiusProperty, "Radius",
        Noesis::FrameworkPropertyMetadata::Create(0.0f,
        Noesis::FrameworkPropertyMetadataOptions_AffectsRender));

    data->OverrideMetadata<Noesis::Stretch>(Shape::StretchProperty, "Stretch",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::Stretch_Fill));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NoesisApp::Star::RatioProperty;
const Noesis::DependencyProperty* NoesisApp::Star::CountProperty;
const Noesis::DependencyProperty* NoesisApp::Star::RadiusProperty;
