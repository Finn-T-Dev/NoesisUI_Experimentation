////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RadialNeedle.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/RotateTransform.h>
#include <NsGui/ContentPropertyMetaData.h>
#include <NsGui/Decorator.h>

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::RadialNeedle::RadialNeedle()
{
    Noesis::Ptr<Noesis::Decorator> decorator = *new Noesis::Decorator(false);
    decorator->SetRenderTransform(Noesis::MakePtr<Noesis::RotateTransform>());
    decorator->SetRenderTransformOrigin(Noesis::Point(0.5f, 1.0f));
    SetSingleVisualChild(decorator);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialNeedle::GetMinimum() const
{
    return DependencyObject::GetValue<float>(MinimumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::SetMinimum(float v)
{
    DependencyObject::SetValue<float>(MinimumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialNeedle::GetMaximum() const
{
    return DependencyObject::GetValue<float>(MaximumProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::SetMaximum(float v)
{
    DependencyObject::SetValue<float>(MaximumProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialNeedle::GetValue() const
{
    return DependencyObject::GetValue<float>(ValueProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::SetValue(float v)
{
    DependencyObject::SetValue<float>(ValueProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialNeedle::GetMinAngle() const
{
    return DependencyObject::GetValue<float>(MinAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::SetMinAngle(float v)
{
    DependencyObject::SetValue<float>(MinAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::RadialNeedle::GetMaxAngle() const
{
    return DependencyObject::GetValue<float>(MaxAngleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::SetMaxAngle(float v)
{
    DependencyObject::SetValue<float>(MaxAngleProperty, v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement* NoesisApp::RadialNeedle::GetChild() const
{
    return ((Noesis::Decorator*)GetSingleVisualChild())->GetChild();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::SetChild(UIElement* child)
{
    Noesis::Decorator* decorator = (Noesis::Decorator*)GetSingleVisualChild();
    Noesis::Ptr<UIElement> oldChild(decorator->GetChild());
    if (oldChild != child)
    {
        decorator->SetChild(0);
        RemoveLogicalChild(oldChild.GetPtr());

        AddLogicalChild(child);
        decorator->SetChild(child);

        InvalidateMeasure();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t NoesisApp::RadialNeedle::GetVisualChildrenCount() const
{
    return 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Visual* NoesisApp::RadialNeedle::GetVisualChild(uint32_t index) const
{
    NS_ASSERT(index == 0u);
    return GetSingleVisualChild();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::CloneOverride(FrameworkElement* clone,
    Noesis::FrameworkTemplate* template_) const
{
    FrameworkElement* child = Noesis::DynamicCast<FrameworkElement*>(GetChild());
    if (child != nullptr)
    {
        RadialNeedle* radialNeedle = (RadialNeedle*)clone;
        if (radialNeedle->GetChild() == nullptr)
        {
            FrameworkElement* templatedParent = radialNeedle->GetTemplatedParent();
            Noesis::Decorator* decorator = (Noesis::Decorator*)radialNeedle->GetSingleVisualChild();
            decorator->SetTemplatedParent(templatedParent, 0);
            Noesis::Ptr<FrameworkElement> childClone = child->Clone(radialNeedle, templatedParent,
                template_);
            radialNeedle->SetChild(childClone);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t NoesisApp::RadialNeedle::GetLogicalChildrenCount() const
{
    return GetChild() != 0 ? 1u : 0u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::BaseComponent> NoesisApp::RadialNeedle::GetLogicalChild(uint32_t) const
{
    return WrapPtr(GetChild());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::RadialNeedle::OnTemplatedParentChanged(FrameworkElement* old_, FrameworkElement* new_)
{
    if (old_ != 0 && new_ == 0)
    {
        // clean templated parent from decorator
        Noesis::Decorator* decorator = (Noesis::Decorator*)GetSingleVisualChild();
        decorator->SetTemplatedParent(0, 0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size NoesisApp::RadialNeedle::MeasureOverride(const Noesis::Size& availableSize)
{
    UIElement* child = (UIElement*)GetSingleVisualChild();

    if (child != nullptr)
    {
        child->Measure(Noesis::Size(FLT_INF, FLT_INF));
    }

    return availableSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size NoesisApp::RadialNeedle::ArrangeOverride(const Noesis::Size& finalSize)
{
    UIElement* child = (UIElement*)GetSingleVisualChild();

    if (child != nullptr)
    {
        const Noesis::Size& desiredSize = child->GetDesiredSize();
        float x = finalSize.width * 0.5f - desiredSize.width * 0.5f;
        float y = finalSize.height * 0.5f - desiredSize.height;
        child->Arrange(Noesis::Rect(Noesis::Point(x, y), desiredSize));
    }

    return finalSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float ValueToAngle(float v, float min, float max, float minAngle, float maxAngle)
{
    return ((Noesis::Clip(v, min, max) - min) / (max - min) * (maxAngle - minAngle)) + minAngle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::RadialNeedle, "NoesisGUIExtensions.RadialNeedle")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<Noesis::StudioOrder>(2000, "Range");
    NsMeta<Noesis::StudioDesc>("Handles the rotation and rendering of the needle within a radial gauge");
    NsMeta<Noesis::StudioHelpUri>("https://www.noesisengine.com/docs/App.Toolkit._RadialBorder.html");
    NsMeta<Noesis::StudioIcon>(Noesis::Uri::Pack("Toolkit", "#ToolkitIcons"), 0xE903);

    NsProp("MinAngle", &NoesisApp::RadialNeedle::GetMinAngle, &NoesisApp::RadialNeedle::SetMinAngle)
        .Meta<Noesis::StudioOrder>(0)
        .Meta<Noesis::StudioRange>(-180.0f, 180.0f);
    NsProp("MaxAngle", &NoesisApp::RadialNeedle::GetMaxAngle, &NoesisApp::RadialNeedle::SetMaxAngle)
        .Meta<Noesis::StudioOrder>(1)
        .Meta<Noesis::StudioRange>(-180.0f, 180.0f);

    NsProp("Value", &NoesisApp::RadialNeedle::GetValue, &NoesisApp::RadialNeedle::SetValue)
        .Meta<Noesis::StudioOrder>(2);

    NsProp("Minimum", &NoesisApp::RadialNeedle::GetMinimum, &NoesisApp::RadialNeedle::SetMinimum)
        .Meta<Noesis::StudioOrder>(3);
    NsProp("Maximum", &NoesisApp::RadialNeedle::GetMaximum, &NoesisApp::RadialNeedle::SetMaximum)
        .Meta<Noesis::StudioOrder>(4);
  #endif

    NsMeta<Noesis::ContentPropertyMetaData>("Child");
    NsProp("Child", &NoesisApp::RadialNeedle::GetChild, &NoesisApp::RadialNeedle::SetChild);

    auto OnValueChanged = [](DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        RadialNeedle* needle = (RadialNeedle*)d;

        float minimum = needle->GetMinimum();
        float maximum = needle->GetMaximum();
        float value = needle->GetValue();
        float minAngle = needle->GetMinAngle();
        float maxAngle = needle->GetMaxAngle();

        float angle = ValueToAngle(value, minimum, maximum, minAngle, maxAngle);
        Noesis::Decorator* decorator = (Noesis::Decorator*)needle->GetSingleVisualChild();
        ((Noesis::RotateTransform*)decorator->GetRenderTransform())->SetAngle(angle);
    };

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());

    data->RegisterProperty<float>(MinimumProperty, "Minimum",
        Noesis::FrameworkPropertyMetadata::Create(0.0f,
        Noesis::PropertyChangedCallback(OnValueChanged)));
    data->RegisterProperty<float>(MaximumProperty, "Maximum",
        Noesis::FrameworkPropertyMetadata::Create(100.0f,
        Noesis::PropertyChangedCallback(OnValueChanged)));
    data->RegisterProperty<float>(ValueProperty, "Value",
        Noesis::FrameworkPropertyMetadata::Create(0.0f,
        Noesis::PropertyChangedCallback(OnValueChanged)));
    data->RegisterProperty<float>(MinAngleProperty, "MinAngle",
        Noesis::FrameworkPropertyMetadata::Create(-120.0f,
        Noesis::PropertyChangedCallback(OnValueChanged)));
    data->RegisterProperty<float>(MaxAngleProperty, "MaxAngle",
        Noesis::FrameworkPropertyMetadata::Create(120.0f,
        Noesis::PropertyChangedCallback(OnValueChanged)));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NoesisApp::RadialNeedle::MinimumProperty;
const Noesis::DependencyProperty* NoesisApp::RadialNeedle::MaximumProperty;
const Noesis::DependencyProperty* NoesisApp::RadialNeedle::ValueProperty;
const Noesis::DependencyProperty* NoesisApp::RadialNeedle::MinAngleProperty;
const Noesis::DependencyProperty* NoesisApp::RadialNeedle::MaxAngleProperty;
