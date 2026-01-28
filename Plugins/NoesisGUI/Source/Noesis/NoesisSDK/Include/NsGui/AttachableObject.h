////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ATTACHABLEOBJECT_H__
#define __GUI_ATTACHABLEOBJECT_H__


#include <NsCore/Noesis.h>
#include <NsGui/Animatable.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/IAttachedObject.h>


namespace Noesis
{

class TypeClass;
NS_INTERFACE IView;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for specifying attachable objects.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API AttachableObject: public Animatable, public IAttachedObject
{
public:
    virtual ~AttachableObject() = 0;

    /// From IAttachedObject
    //@{
    DependencyObject* GetAssociatedObject() const override;
    void Attach(DependencyObject* associatedObject) override;
    void Detach() override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    AttachableObject(const TypeClass* associatedType);

    // For internal use only
    //@{
    AttachableObject();
    void SetAssociatedType(const TypeClass* associatedType);
    //@}

    // Gets the View where this object is attached to
    IView* GetView() const;

    // Called after the object is attached to an AssociatedObject
    virtual void OnAttached();

    // Called just before the object is detached from its AssociatedObject
    virtual void OnDetaching();

private:
    void OnAttachedDestroyed(DependencyObject* d);
    void OnViewDestroyed(FrameworkElement* content);

private:
    const TypeClass* mAssociatedType;
    DependencyObject* mAssociatedObject;
    mutable IView* mView;

    NS_DECLARE_REFLECTION(AttachableObject, Animatable)
};

NS_WARNING_POP

}


#endif
