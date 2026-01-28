////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMPARISONLOGIC_H__
#define __GUI_COMPARISONLOGIC_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/ComparisonCondition.h>


namespace Noesis
{

template<class T> class Ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper class that evaluates logic operations.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API ComparisonLogic: public BaseComponent
{
public:
    /// Obtains the type of the boxed value
    static const Type* ExtractBoxedType(BaseComponent* value);

    /// Creates a ComparisonLogic object for the specified type
    static Ptr<ComparisonLogic> Create(const Type* type);

    /// Evaluates the specified binary oparation
    virtual bool Evaluate(BaseComponent* left, ComparisonConditionType comparison,
        BaseComponent* right) const = 0;

    NS_DECLARE_REFLECTION(ComparisonLogic, BaseComponent)
};

}

#endif
