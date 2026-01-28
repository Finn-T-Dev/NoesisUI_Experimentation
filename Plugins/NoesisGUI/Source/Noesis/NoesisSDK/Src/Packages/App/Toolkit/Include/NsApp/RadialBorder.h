////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RADIALBORDER_H__
#define __APP_RADIALBORDER_H__


#include <NsCore/Noesis.h>
#include <NsApp/ToolkitApi.h>
#include <NsGui/FrameworkElement.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Renders the border of the scale on a radial gauge
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_TOOLKIT_API RadialBorder final: public Noesis::FrameworkElement
{
public:
    RadialBorder();

    /// Gets or sets the minimum possible Value
    //@{
    float GetMinimum() const;
    void SetMinimum(float v);
    //@}

    /// Gets or sets the highest possible Value
    //@{
    float GetMaximum() const;
    void SetMaximum(float v);
    //@}

    /// Gets or sets the start value of the border
    //@{
    float GetStart() const;
    void SetStart(float v);
    //@}

    /// Gets or sets the end value of the border
    //@{
    float GetEnd() const;
    void SetEnd(float v);
    //@}

    /// Gets or sets the width of the border
    //@{
    float GetBorderWidth() const;
    void SetBorderWidth(float v);
    //@}

    /// Gets or sets the distance of the border from the outside of the control
    //@{
    float GetPadding() const;
    void SetPadding(float v);
    //@}

    /// Gets or sets the border brush
    //@{
    Noesis::Brush* GetBrush() const;
    void SetBrush(Noesis::Brush* v);
    //@}

    /// Gets or sets the start angle, which corresponds with the minimum value, in degrees
    //@{
    float GetMinAngle() const;
    void SetMinAngle(float v);
    //@}

    /// Gets or sets the end angle, which corresponds with the maximum value, in degrees
    //@{
    float GetMaxAngle() const;
    void SetMaxAngle(float v);
    //@}

public:
    /// Dependency properties
    //@{
    static const Noesis::DependencyProperty* MinimumProperty;
    static const Noesis::DependencyProperty* MaximumProperty;
    static const Noesis::DependencyProperty* StartProperty;
    static const Noesis::DependencyProperty* EndProperty;
    static const Noesis::DependencyProperty* BorderWidthProperty;
    static const Noesis::DependencyProperty* PaddingProperty;
    static const Noesis::DependencyProperty* BrushProperty;
    static const Noesis::DependencyProperty* MinAngleProperty;
    static const Noesis::DependencyProperty* MaxAngleProperty;
    //@}

private:
    void OnRender(Noesis::DrawingContext* context) override;

    NS_DECLARE_REFLECTION(RadialBorder, FrameworkElement)
};

}

#endif
