////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONDITIONALEXPRESSION_H__
#define __GUI_CONDITIONALEXPRESSION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/Animatable.h>


namespace Noesis
{

class ComparisonCondition;
template<class T> class FreezableCollection;
typedef FreezableCollection<ComparisonCondition> ComparisonConditionCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
enum ForwardChaining
{
    ForwardChaining_And,
    ForwardChaining_Or
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a conditional expression that is set on a ConditionBehavior *Condition* property.
/// Contains a list of conditions that gets evaluated in order.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API ConditionalExpression: public Animatable
{
public:
    ConditionalExpression();
    ~ConditionalExpression();

    /// Gets or sets forward chaining for the conditions
    /// If forward chaining is set to *And*, all conditions must be met
    /// If forward chaining is set to *Or*, only one condition must be met
    //@{
    ForwardChaining GetForwardChaining() const;
    void SetForwardChaining(ForwardChaining value);
    //@}

    /// Returns the collection of ComparisonCondition objects
    ComparisonConditionCollection* GetConditions() const;

    /// Goes through the *Conditions* collection and evalutes each condition based on the value of
    /// *ForwardChaining* property. Returns true if conditions are met; otherwise, returns false
    bool Evaluate() const;

public:
    static const DependencyProperty* ForwardChainingProperty;
    static const DependencyProperty* ConditionsProperty;

protected:
    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

    NS_DECLARE_REFLECTION(ConditionalExpression, Animatable)
};

}

NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_INTERACTIVITY_API, Noesis::ForwardChaining)


#endif
