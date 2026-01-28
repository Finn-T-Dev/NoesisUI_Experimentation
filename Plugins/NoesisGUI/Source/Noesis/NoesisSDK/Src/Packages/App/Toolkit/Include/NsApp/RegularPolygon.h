////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_REGULARPOLYGON_H__
#define __APP_REGULARPOLYGON_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsApp/ToolkitApi.h>
#include <NsGui/Shape.h>


namespace Noesis
{
class StreamGeometry;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Renders a regular polygon shape with variable number of points
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_TOOLKIT_API RegularPolygon final: public Noesis::Shape
{
public:
    RegularPolygon();
    ~RegularPolygon();

    /// Gets or sets the number of points
    //@{
    uint32_t GetCount() const;
    void SetCount(uint32_t v);
    //@}

    /// Gets or sets the radius in pixels that is used to round the points
    //@{
    float GetRadius() const;
    void SetRadius(float v);
    //@}

public:
    /// Dependency properties
    //@{
    static const Noesis::DependencyProperty* CountProperty;
    static const Noesis::DependencyProperty* RadiusProperty;
    //@}

protected:
    /// From UIElement
    //@{
    void OnRender(Noesis::DrawingContext* context) override;
    //@}

    /// From FrameworkElement
    //@{
    Noesis::Size MeasureOverride(const Noesis::Size& availableSize) override;
    Noesis::Size ArrangeOverride(const Noesis::Size& finalSize) override;
    //@}

    /// From Shape
    //@{
    Noesis::Geometry* GetRenderGeometry() const override;
    //@}

private:
    Noesis::Rect mRect;
    Noesis::Ptr<Noesis::StreamGeometry> mRenderGeometry;

    NS_DECLARE_REFLECTION(RegularPolygon, Shape)
};

NS_WARNING_POP

}


#endif
