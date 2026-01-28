////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BEHAVIORCOLLECTION_H__
#define __GUI_BEHAVIORCOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/AttachableCollection.h>
#include <NsGui/Behavior.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of behaviors with a shared *AssociatedObject* and provides change
/// notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API BehaviorCollection final: public AttachableCollection<Behavior>
{
public:
    BehaviorCollection();
    ~BehaviorCollection();

    // Hides Freezable methods for convenience
    //@{
    Ptr<BehaviorCollection> Clone() const;
    Ptr<BehaviorCollection> CloneCurrentValue() const;
    //@}

private:
    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    bool FreezeCore(bool isChecking) override;
    //@}

    /// From AttachableCollection
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    void ItemAdded(Behavior* item) override;
    void ItemRemoved(Behavior* item) override;
    //@}

    NS_DECLARE_REFLECTION(BehaviorCollection, AttachableCollection)
};

NS_WARNING_POP

}


#endif
