////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BEHAVIOR_H__
#define __GUI_BEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsGui/AttachableObject.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for specifying *Behaviors* for a DependencyObject.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API Behavior: public AttachableObject
{
public:
    virtual ~Behavior() = 0;

    // Hides Freezable methods for convenience
    //@{
    Ptr<Behavior> Clone() const;
    Ptr<Behavior> CloneCurrentValue() const;
    //@}

protected:
    Behavior(const TypeClass* associatedType);

    // For internal use only
    Behavior();

    NS_DECLARE_REFLECTION(Behavior, AttachableObject)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for *Behaviors*.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class BehaviorT: public Behavior
{
public:
    inline T* GetAssociatedObject() const
    {
        return static_cast<T*>(ParentClass::GetAssociatedObject());
    }

protected:
    inline BehaviorT(): Behavior(TypeOf<T>()) { }
    NS_IMPLEMENT_INLINE_REFLECTION_(BehaviorT, Behavior)
};

NS_WARNING_POP

}


#endif
