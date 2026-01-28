////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RADIALGAUGE_H__
#define __APP_RADIALGAUGE_H__


#include <NsCore/Noesis.h>
#include <NsApp/ToolkitApi.h>
#include <NsGui/RangeBase.h>


namespace Noesis
{
class SolidColorBrush;
}

namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a radial gauge with customizable elements such as needle, ticks, and border
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_TOOLKIT_API RadialGauge final: public Noesis::RangeBase
{
public:
    RadialGauge();

    /// Gets or sets the width of the scale
    //@{
    float GetScaleWidth() const;
    void SetScaleWidth(float v);
    //@}

    /// Gets or sets the scale brush
    //@{
    Noesis::SolidColorBrush* GetScaleBrush() const;
    void SetScaleBrush(Noesis::SolidColorBrush* v);
    //@}

    /// Gets or sets the distance of the scale from the outside of the control
    //@{
    float GetScalePadding() const;
    void SetScalePadding(float v);
    //@}

    /// Gets or sets the needle brush
    //@{
    Noesis::SolidColorBrush* GetNeedleBrush() const;
    void SetNeedleBrush(Noesis::SolidColorBrush* v);
    //@}

    /// Gets or sets the needle length
    //@{
    float GetNeedleLength() const;
    void SetNeedleLength(float v);
    //@}

    /// Gets or sets the needle width
    //@{
    float GetNeedleWidth() const;
    void SetNeedleWidth(float v);
    //@}

    /// Gets or sets the trail brush
    //@{
    Noesis::SolidColorBrush* GetTrailBrush() const;
    void SetTrailBrush(Noesis::SolidColorBrush* v);
    //@}

    /// Gets or sets the outer tick brush
    //@{
    Noesis::SolidColorBrush* GetTickBrush() const;
    void SetTickBrush(Noesis::SolidColorBrush* v);
    //@}

    /// Gets or sets the distance of the ticks from the outside of the control
    //@{
    float GetTickPadding() const;
    void SetTickPadding(float v);
    //@}

    /// Gets or sets the width of the ticks, in percentage of the gauge radius
    //@{
    float GetTickWidth() const;
    void SetTickWidth(float v);
    //@}

    /// Gets or sets the length of the ticks
    //@{
    float GetTickLength() const;
    void SetTickLength(float v);
    //@}

    /// Gets or sets the tick spacing
    //@{
    float GetTickSpacing() const;
    void SetTickSpacing(float v);
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
    static const Noesis::DependencyProperty* ScaleWidthProperty;
    static const Noesis::DependencyProperty* ScaleBrushProperty;
    static const Noesis::DependencyProperty* ScalePaddingProperty;
    static const Noesis::DependencyProperty* NeedleBrushProperty;
    static const Noesis::DependencyProperty* NeedleLengthProperty;
    static const Noesis::DependencyProperty* NeedleWidthProperty;
    static const Noesis::DependencyProperty* TrailBrushProperty;
    static const Noesis::DependencyProperty* TickBrushProperty;
    static const Noesis::DependencyProperty* TickSpacingProperty;
    static const Noesis::DependencyProperty* TickWidthProperty;
    static const Noesis::DependencyProperty* TickLengthProperty;
    static const Noesis::DependencyProperty* TickPaddingProperty;
    static const Noesis::DependencyProperty* MinAngleProperty;
    static const Noesis::DependencyProperty* MaxAngleProperty;
    //@}

private:
    NS_DECLARE_REFLECTION(RadialGauge, RangeBase)
};

}

#endif
