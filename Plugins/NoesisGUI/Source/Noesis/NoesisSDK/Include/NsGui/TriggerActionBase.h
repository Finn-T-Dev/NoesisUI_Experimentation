////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGERACTIONBASE_H__
#define __GUI_TRIGGERACTIONBASE_H__


#include <NsCore/Noesis.h>
#include <NsGui/AttachableObject.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an attachable object that encapsulates a unit of functionality.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API TriggerActionBase: public AttachableObject
{
public:
    virtual ~TriggerActionBase() = 0;

    /// Gets or sets a value indicating whether this action will run when invoked
    //@{
    bool GetIsEnabled() const;
    void SetIsEnabled(bool isEnabled);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Ptr<TriggerActionBase> Clone() const;
    Ptr<TriggerActionBase> CloneCurrentValue() const;
    //@}

public:
    static const DependencyProperty* IsEnabledProperty;

protected:
    TriggerActionBase(const TypeClass* associatedType);

    // For internal use only
    TriggerActionBase();

    // Invokes the action
    virtual void Invoke(BaseComponent* parameter) = 0;

private:
    // Used by TriggerBase to try to invoke the action
    friend class TriggerBase;
    void CallInvoke(BaseComponent* parameter);

    NS_DECLARE_REFLECTION(TriggerActionBase, AttachableObject)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for TriggerAction.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class TriggerActionBaseT: public TriggerActionBase
{
public:
    inline T* GetAssociatedObject() const
    {
        return static_cast<T*>(ParentClass::GetAssociatedObject());
    }

protected:
    inline TriggerActionBaseT(): TriggerActionBase(TypeOf<T>()) { }

    NS_IMPLEMENT_INLINE_REFLECTION_(TriggerActionBaseT, TriggerActionBase)
};

NS_WARNING_POP

}


#endif
