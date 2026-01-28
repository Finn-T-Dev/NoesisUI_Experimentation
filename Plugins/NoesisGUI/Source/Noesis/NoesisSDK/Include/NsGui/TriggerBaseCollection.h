////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGERBASECOLLECTION_H__
#define __GUI_TRIGGERBASECOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/AttachableCollection.h>
#include <NsGui/TriggerBase.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of triggers with a shared *AssociatedObject* and provides change
/// notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API TriggerBaseCollection final: public AttachableCollection<TriggerBase>
{
public:
    TriggerBaseCollection();
    ~TriggerBaseCollection();

    // Hides Freezable methods for convenience
    //@{
    Ptr<TriggerBaseCollection> Clone() const;
    Ptr<TriggerBaseCollection> CloneCurrentValue() const;
    //@}

private:
    // From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    bool FreezeCore(bool isChecking) override;
    //@}

    // From AttachableCollection
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    void ItemAdded(TriggerBase* item) override;
    void ItemRemoved(TriggerBase* item) override;
    //@}

    NS_DECLARE_REFLECTION(TriggerBaseCollection, AttachableCollection)
};

NS_WARNING_POP

}


#endif
