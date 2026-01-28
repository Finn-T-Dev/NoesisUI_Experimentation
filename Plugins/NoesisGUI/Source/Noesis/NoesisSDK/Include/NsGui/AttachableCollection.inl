////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline AttachableCollection<T>::AttachableCollection(): mAssociatedObject(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline AttachableCollection<T>::~AttachableCollection()
{
    if (mAssociatedObject != 0)
    {
        mAssociatedObject->Destroyed() -= MakeDelegate(this,
            &AttachableCollection::OnAttachedDestroyed);
        mAssociatedObject = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline DependencyObject* AttachableCollection<T>::GetAssociatedObject() const
{
    return mAssociatedObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AttachableCollection<T>::Attach(DependencyObject* associatedObject)
{
    if (mAssociatedObject != associatedObject)
    {
        if (mAssociatedObject != 0)
        {
            NS_ERROR("'%s' already attached to another object '%s'",
                GetClassType()->GetName(), mAssociatedObject->GetClassType()->GetName());
            return;
        }

        NS_ASSERT(associatedObject != 0);
        mAssociatedObject = associatedObject;
        mAssociatedObject->Destroyed() += MakeDelegate(this,
            &AttachableCollection::OnAttachedDestroyed);

        InitComponent(this, true);

        OnAttached();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AttachableCollection<T>::Detach()
{
    if (mAssociatedObject != 0)
    {
        OnDetaching();

        mAssociatedObject->Destroyed() -= MakeDelegate(this,
            &AttachableCollection::OnAttachedDestroyed);
        mAssociatedObject = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AttachableCollection<T>::OnAttachedDestroyed(DependencyObject* d)
{
    NS_ASSERT(mAssociatedObject == d);
    Detach();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AttachableCollection<T>::InsertItem(uint32_t index, BaseComponent* item)
{
    ParentClass::InsertItem(index, item);

    ItemAdded(static_cast<T*>(item));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AttachableCollection<T>::SetItem(uint32_t index, BaseComponent* item)
{
    ItemRemoved(static_cast<T*>(this->mItems[index].GetPtr()));

    ParentClass::SetItem(index, item);

    ItemAdded(static_cast<T*>(item));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AttachableCollection<T>::RemoveItem(uint32_t index)
{
    ItemRemoved(static_cast<T*>(this->mItems[index].GetPtr()));

    ParentClass::RemoveItem(index);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AttachableCollection<T>::ClearItems()
{
    int numItems = this->Count();
    for (int i = numItems - 1; i >= 0; --i)
    {
        ItemRemoved(static_cast<T*>(this->mItems[i].GetPtr()));
    }

    ParentClass::ClearItems();
}

}
