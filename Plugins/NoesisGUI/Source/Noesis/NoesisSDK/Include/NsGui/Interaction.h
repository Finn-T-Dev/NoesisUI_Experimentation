////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INTERACTION_H__
#define __GUI_INTERACTION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/InteractivityApi.h>


namespace Noesis
{

class BehaviorCollection;
class TriggerBaseCollection;
class DependencyObject;
class DependencyProperty;

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manages a collection of behaviors and triggers that expand the object functionality from XAML.
///
/// .. code-block:: xml
///
///    <UserControl
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <b:Interaction.Behaviors>
///        <b:MouseDragElementBehavior />
///      <b:Interaction.Behaviors>
///      <b:Interaction.Triggers>
///        <b:EventTrigger EventName="Loaded">
///          <b:GoToStateAction StateName="Init" />
///        </b:EventTrigger>
///      <b:Interaction.Triggers>
///    </UserControl>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_INTERACTIVITY_API Interaction
{
    /// Gets the value of the Behaviors attached property
    static BehaviorCollection* GetBehaviors(const DependencyObject* obj);

    /// Gets the value of the Triggers attached property
    static TriggerBaseCollection* GetTriggers(const DependencyObject* obj);

private:
    static const DependencyProperty* BehaviorsProperty; // Attached
    static const DependencyProperty* TriggersProperty; // Attached

    NS_DECLARE_REFLECTION(Interaction, NoParent)
};

NS_WARNING_POP

}


#endif
