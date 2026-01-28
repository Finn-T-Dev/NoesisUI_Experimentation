////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_NOISEEFFECT_H__
#define __APP_NOISEEFFECT_H__


#include <NsApp/ShadersApi.h>
#include <NsGui/ShaderEffect.h>
#include <NsRender/RenderContext.h>


namespace Noesis { class DependencyProperty; }

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Noise effect simulates high-speed film grain, adding random pixel patterns.
///
/// .. code-block:: xml
///
///  <StackPanel
///    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///    xmlns:noesis="clr-namespace:NoesisGUIExtensions"
///    Orientation="Horizontal">
///    <Image Source="Images/tulip.png"/>
///    <Image Source="Images/tulip.png">
///      <Image.Effect>
///       <noesis:NoiseEffect Amount="0.45"/>
///      </Image.Effect>
///    </Image>
///  </StackPanel>
///
/// .. image:: Noise.jpg
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_SHADERS_API NoiseEffect final: public Noesis::ShaderEffect
{
public:
    NoiseEffect();

    /// Gets or sets the amount of noise, ranging from 0.0 to 1.0
    //@{
    float GetAmount() const;
    void SetAmount(float value);
    //@}

    /// Gets or sets the time parameter associated with animating the noise effect
    //@{
    float GetTime() const;
    void SetTime(float value);
    //@}

    /// Gets or sets whether the noise is grayscale or multicolored
    //@{
    bool GetMonochromatic() const;
    void SetMonochromatic(bool value);
    //@}

public:
    static const Noesis::DependencyProperty* AmountProperty;
    static const Noesis::DependencyProperty* TimeProperty;
    static const Noesis::DependencyProperty* MonochromaticProperty;
    static EffectShaders Shaders;

private:
    struct Constants
    {
        float amount = 0.50f;
        float time = 0.0f;
        uint32_t monochromatic = 0;
    };

    Constants mConstants;

    NS_DECLARE_REFLECTION(NoiseEffect, ShaderEffect)
};

NS_WARNING_POP

}

#endif
