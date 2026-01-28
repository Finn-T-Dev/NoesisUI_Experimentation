////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STYLEINTERACTION_H__
#define __GUI_STYLEINTERACTION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/Behavior.h>
#include <NsGui/TriggerBase.h>
#include <NsGui/FreezableCollection.h>


namespace Noesis
{

class DependencyObject;
class DependencyProperty;
struct DependencyPropertyChangedEventArgs;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A collection that specifies the list of interactivity behaviors to be added to the element
/// when the style is applied
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API StyleBehaviorCollection final: public FreezableCollection<Behavior>
{
    NS_DECLARE_REFLECTION(StyleBehaviorCollection, BaseFreezableCollection)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A collection that specifies the list of interactivity triggers to be added to the element
/// when the style is applied
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API StyleTriggerCollection final: public FreezableCollection<TriggerBase>
{
    NS_DECLARE_REFLECTION(StyleTriggerCollection, BaseFreezableCollection)
};

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Allows setting a collection of *Interactivity* behaviors and triggers in a Style, so they are
/// applied to all instances of the styled control.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <Grid.Resources>
///        <Style TargetType="Button" BasedOn="{StaticResource {x:Type Button}}">
///          <Setter Property="noesis:StyleInteraction.Triggers">
///            <Setter.Value>
///              <noesis:StyleTriggerCollection>
///                <b:EventTrigger EventName="Click">
///                  <b:PlaySoundAction Source="Sounds/ButtonClick.wav" />
///                </b:EventTrigger>
///              </noesis:StyleTriggerCollection>
///            </Setter.Value>
///          </Setter>
///        </Style>
///      </Grid.Resources>
///      ...
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_INTERACTIVITY_API StyleInteraction
{
    static const DependencyProperty* BehaviorsProperty;
    static const DependencyProperty* TriggersProperty;

    NS_DECLARE_REFLECTION(StyleInteraction, NoParent);
};

NS_WARNING_POP

}


#endif
