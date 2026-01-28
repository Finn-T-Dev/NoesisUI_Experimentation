////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ATTACHABLECOLLECTION_H__
#define __GUI_ATTACHABLECOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/IAttachedObject.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of IAttachedObject with a shared *AssociatedObject* and provides
/// change notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class AttachableCollection: public FreezableCollection<T>, public IAttachedObject
{
public:
    inline virtual ~AttachableCollection() = 0;

    /// From IAttachedObject
    //@{
    DependencyObject* GetAssociatedObject() const final;
    void Attach(DependencyObject* associatedObject) final;
    void Detach() final;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    AttachableCollection();

    // Called immediately after the collection is attached to an AssociatedObject
    virtual void OnAttached() = 0;

    // Called when the collection is being detached from its AssociatedObject, but before it has
    // actually occurred
    virtual void OnDetaching() = 0;

    // Called when a new item is added to the collection
    virtual void ItemAdded(T* item) = 0;

    // Called when an item is removed from the collection
    virtual void ItemRemoved(T* item) = 0;

private:
    void OnAttachedDestroyed(DependencyObject* d);

    /// From FreezableCollection
    //@{
    void InsertItem(uint32_t index, BaseComponent* item) final;
    void SetItem(uint32_t index, BaseComponent* item) final;
    void RemoveItem(uint32_t index) final;
    void ClearItems() final;
    //@}

private:
    DependencyObject* mAssociatedObject;

    NS_IMPLEMENT_INLINE_REFLECTION(AttachableCollection<T>, BaseFreezableCollection)
    {
        NsImpl<IAttachedObject>();
    }
};

}

#include <NsGui/AttachableCollection.inl>


#endif
