////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RADIALTICKS_H__
#define __APP_RADIALTICKS_H__


#include <NsCore/Noesis.h>
#include <NsApp/ToolkitApi.h>
#include <NsGui/FrameworkElement.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Renders ticks on a radial gauge
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_TOOLKIT_API RadialTicks final: public Noesis::FrameworkElement
{
public:
    RadialTicks();

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

    /// Gets or sets the width of the scale ticks
    //@{
    float GetTickWidth() const;
    void SetTickWidth(float v);
    //@}

    /// Gets or sets the length of the ticks
    //@{
    float GetTickLength() const;
    void SetTickLength(float v);
    //@}

    /// Gets or sets the distance of the ticks from the outside of the control
    //@{
    float GetPadding() const;
    void SetPadding(float v);
    //@}

    /// Gets or sets the tick spacing
    //@{
    float GetSpacing() const;
    void SetSpacing(float v);
    //@}

    /// Gets or sets the tick brush
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
    static const Noesis::DependencyProperty* TickWidthProperty;
    static const Noesis::DependencyProperty* TickLengthProperty;
    static const Noesis::DependencyProperty* PaddingProperty;
    static const Noesis::DependencyProperty* SpacingProperty;
    static const Noesis::DependencyProperty* BrushProperty;
    static const Noesis::DependencyProperty* MinAngleProperty;
    static const Noesis::DependencyProperty* MaxAngleProperty;
    //@}

private:
    void OnRender(Noesis::DrawingContext* context) override;

    NS_DECLARE_REFLECTION(RadialTicks, FrameworkElement)
};

}

#endif
