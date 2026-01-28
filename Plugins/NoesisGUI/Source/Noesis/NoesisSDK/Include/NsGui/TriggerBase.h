////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGERBASE_H__
#define __GUI_TRIGGERBASE_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsGui/AttachableObject.h>
#include <NsGui/Events.h>


namespace Noesis
{

class TriggerActionBaseCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PreviewInvoke event args. Assigning Cancelling to True will cancel the invoking of the trigger.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct PreviewInvokeEventArgs: public EventArgs
{
    mutable bool cancelling;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Delegate<void (BaseComponent*, const PreviewInvokeEventArgs&)> PreviewInvokeEventHandler;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an object that can invoke *Actions* conditionally.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API TriggerBase: public AttachableObject
{
public:
    virtual ~TriggerBase() = 0;

    /// Gets the actions associated with this trigger
    TriggerActionBaseCollection* GetActions() const;

    /// Raised just before invoking all associated actions
    DelegateEvent_<PreviewInvokeEventHandler> PreviewInvoke();

    // Hides Freezable methods for convenience
    //@{
    Ptr<TriggerBase> Clone() const;
    Ptr<TriggerBase> CloneCurrentValue() const;
    //@}

public:
    static const DependencyProperty* ActionsProperty;

protected:
    TriggerBase(const TypeClass* associatedType);

    // For internal use only
    TriggerBase();

    // Invoke all actions associated with this trigger
    void InvokeActions(BaseComponent* parameter);

    /// From DependencyObject
    //@{
    void OnInit() override;
    //@}

    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source) override;
    //@}

    /// From AttachableObject
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

private:
    PreviewInvokeEventHandler mPreviewInvoke;

    NS_DECLARE_REFLECTION(TriggerBase, AttachableObject)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for TriggerBase.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class TriggerBaseT: public TriggerBase
{
public:
    inline T* GetAssociatedObject() const
    {
        return static_cast<T*>(ParentClass::GetAssociatedObject());
    }

protected:
    inline TriggerBaseT(): TriggerBase(TypeOf<T>()) { }

    NS_IMPLEMENT_INLINE_REFLECTION_(TriggerBaseT, TriggerBase)
};

NS_WARNING_POP

}


#endif
