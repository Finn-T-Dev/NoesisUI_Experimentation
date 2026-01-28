////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RADIALNEEDLE_H__
#define __APP_RADIALNEEDLE_H__


#include <NsCore/Noesis.h>
#include <NsApp/ToolkitApi.h>
#include <NsGui/FrameworkElement.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Handles the rotation and rendering of the needle within a radial gauge
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_TOOLKIT_API RadialNeedle final: public Noesis::FrameworkElement
{
public:
    RadialNeedle();

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

    /// Gets or sets the current value
    //@{
    float GetValue() const;
    void SetValue(float v);
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

    /// Gets or sets the needle element
    //@{
    UIElement* GetChild() const;
    void SetChild(UIElement* child);
    //@}

public:
    /// Dependency properties
    //@{
    static const Noesis::DependencyProperty* MinimumProperty;
    static const Noesis::DependencyProperty* MaximumProperty;
    static const Noesis::DependencyProperty* ValueProperty;
    static const Noesis::DependencyProperty* MinAngleProperty;
    static const Noesis::DependencyProperty* MaxAngleProperty;
    //@}

private:
    /// From Visual
    //@{
    uint32_t GetVisualChildrenCount() const override;
    Visual* GetVisualChild(uint32_t index) const override;
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, Noesis::FrameworkTemplate* template_) const override;
    uint32_t GetLogicalChildrenCount() const override;
    Noesis::Ptr<BaseComponent> GetLogicalChild(uint32_t index) const override;
    void OnTemplatedParentChanged(FrameworkElement* old_, FrameworkElement* new_) override;
    Noesis::Size MeasureOverride(const Noesis::Size& availableSize) override;
    Noesis::Size ArrangeOverride(const Noesis::Size& finalSize) override;
    //@}

    NS_DECLARE_REFLECTION(RadialNeedle, FrameworkElement)
};

}

#endif
