////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RADIALNUMBERS_H__
#define __APP_RADIALNUMBERS_H__


#include <NsCore/Noesis.h>
#include <NsApp/ToolkitApi.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
class FontFamily;
}

namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Renders the numerical labels on a radial gauge
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_TOOLKIT_API RadialNumbers final: public Noesis::FrameworkElement
{
public:
    RadialNumbers();

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

    /// Gets or sets the distance of the numbers from the outside of the control
    //@{
    float GetPadding() const;
    void SetPadding(float v);
    //@}

    /// Gets or sets the number spacing
    //@{
    float GetSpacing() const;
    void SetSpacing(float v);
    //@}

    /// Gets or sets the text brush
    //@{
    Noesis::Brush* GetBrush() const;
    void SetBrush(Noesis::Brush* v);
    //@}

    /// Gets or sets the font family for the numbers
    //@{
    Noesis::FontFamily* GetFontFamily() const;
    void SetFontFamily(Noesis::FontFamily* v);
    //@}

    /// Gets or sets the font size for the numbers
    //@{
    float GetFontSize() const;
    void SetFontSize(float v);
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

    /// Gets or sets if numbers are rotated
    //@{
    bool GetRotated() const;
    void SetRotated(bool v);
    //@}

public:
    /// Dependency properties
    //@{
    static const Noesis::DependencyProperty* MinimumProperty;
    static const Noesis::DependencyProperty* MaximumProperty;
    static const Noesis::DependencyProperty* PaddingProperty;
    static const Noesis::DependencyProperty* SpacingProperty;
    static const Noesis::DependencyProperty* BrushProperty;
    static const Noesis::DependencyProperty* FontFamilyProperty;
    static const Noesis::DependencyProperty* FontSizeProperty;
    static const Noesis::DependencyProperty* MinAngleProperty;
    static const Noesis::DependencyProperty* MaxAngleProperty;
    static const Noesis::DependencyProperty* RotatedProperty;
    //@}

private:
    void OnRender(Noesis::DrawingContext* context) override;

    NS_DECLARE_REFLECTION(RadialNumbers, FrameworkElement)
};

}

#endif
