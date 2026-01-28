////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/NoiseEffect.h>
#include <NsCore/ReflectionImplement.h>
#include <NsGui/UIElementData.h>
#include <NsGui/UIPropertyMetadata.h>

#ifdef HAVE_CUSTOM_SHADERS
#include "Noise.bin.h"
#endif

#ifdef NS_HAVE_STUDIO
#include <NsGui/StudioMeta.h>
#endif


using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
NoiseEffect::NoiseEffect()
{
  #ifdef HAVE_CUSTOM_SHADERS
    RenderContext::EnsureShaders(Shaders, "Noise", Noise_bin);
  #endif

    SetPixelShader(Shaders.shaders[0]);
    SetConstantBuffer(&mConstants, sizeof(mConstants));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoiseEffect::GetAmount() const
{
    return GetValue<float>(AmountProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoiseEffect::SetAmount(float value)
{
    SetValue<float>(AmountProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoiseEffect::GetTime() const
{
    return GetValue<float>(TimeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoiseEffect::SetTime(float value)
{
    SetValue<float>(TimeProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoiseEffect::GetMonochromatic() const
{
    return GetValue<bool>(MonochromaticProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoiseEffect::SetMonochromatic(bool value)
{
    SetValue<bool>(MonochromaticProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoiseEffect, "NoesisGUIExtensions.NoiseEffect")
{
  #ifdef NS_HAVE_STUDIO
    NsProp("Amount", &NoiseEffect::GetAmount, &NoiseEffect::SetAmount)
        .Meta<StudioOrder>(0)
        .Meta<StudioRange>(0.0f, 1.0f);
    NsProp("Time", &NoiseEffect::GetTime, &NoiseEffect::SetTime)
        .Meta<StudioOrder>(1)
        .Meta<StudioMin>(0.0f);
    NsProp("Monochromatic", &NoiseEffect::GetMonochromatic, &NoiseEffect::SetMonochromatic)
        .Meta<StudioOrder>(2);
  #endif

    auto OnAmountChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
    {
        NoiseEffect* this_ = (NoiseEffect*)o;
        this_->mConstants.amount = args.NewValue<float>();
        this_->InvalidateConstantBuffer();
    };

    auto OnTimeChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
    {
        NoiseEffect* this_ = (NoiseEffect*)o;
        this_->mConstants.time = args.NewValue<float>();
        this_->InvalidateConstantBuffer();
    };

    auto OnMonochromaticChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
    {
        NoiseEffect* this_ = (NoiseEffect*)o;
        this_->mConstants.monochromatic = args.NewValue<bool>() ? 1 : 0;
        this_->InvalidateConstantBuffer();
    };

    UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
    data->RegisterProperty<float>(AmountProperty, "Amount", UIPropertyMetadata::Create(
        0.50f, PropertyChangedCallback(OnAmountChanged)));
    data->RegisterProperty<float>(TimeProperty, "Time", UIPropertyMetadata::Create(
        0.0f, PropertyChangedCallback(OnTimeChanged)));
    data->RegisterProperty<bool>(MonochromaticProperty, "Monochromatic", UIPropertyMetadata::Create(
        false, PropertyChangedCallback(OnMonochromaticChanged)));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* NoiseEffect::AmountProperty;
const DependencyProperty* NoiseEffect::TimeProperty;
const DependencyProperty* NoiseEffect::MonochromaticProperty;
EffectShaders NoiseEffect::Shaders;
