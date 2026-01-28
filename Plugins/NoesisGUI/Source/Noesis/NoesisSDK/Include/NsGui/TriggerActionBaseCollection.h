////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGERACTIONBASECOLLECTION_H__
#define __GUI_TRIGGERACTIONBASECOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/AttachableCollection.h>
#include <NsGui/TriggerActionBase.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of actions with a shared *AssociatedObject* and provides change
/// notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API TriggerActionBaseCollection final: public AttachableCollection<TriggerActionBase>
{
public:
    TriggerActionBaseCollection();
    ~TriggerActionBaseCollection();

    // Hides Freezable methods for convenience
    //@{
    Ptr<TriggerActionBaseCollection> Clone() const;
    Ptr<TriggerActionBaseCollection> CloneCurrentValue() const;
    //@}

private:
    // From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

    // From AttachableCollection
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    void ItemAdded(TriggerActionBase* item) override;
    void ItemRemoved(TriggerActionBase* item) override;
    //@}

    NS_DECLARE_REFLECTION(TriggerActionBaseCollection, AttachableCollection)
};

NS_WARNING_POP

}


#endif
