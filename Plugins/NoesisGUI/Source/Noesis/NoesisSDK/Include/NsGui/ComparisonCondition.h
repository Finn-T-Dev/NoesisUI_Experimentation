////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMPARISONCONDITION_H__
#define __GUI_COMPARISONCONDITION_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/InteractivityApi.h>
#include <NsGui/Animatable.h>


namespace Noesis
{

class TypeConverter;
class ComparisonLogic;

////////////////////////////////////////////////////////////////////////////////////////////////////
enum ComparisonConditionType
{
    ComparisonConditionType_Equal,
    ComparisonConditionType_NotEqual,
    ComparisonConditionType_LessThan,
    ComparisonConditionType_LessThanOrEqual,
    ComparisonConditionType_GreaterThan,
    ComparisonConditionType_GreaterThanOrEqual
};

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents one ternary condition: *left operand*, *operator*, *right operand*. Used as condition
/// in the list of conditions on a ConditionalExpression.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_INTERACTIVITY_API ComparisonCondition: public Animatable
{
public:
    ComparisonCondition();
    ~ComparisonCondition();

    /// Gets or sets the left operand
    //@{
    BaseComponent* GetLeftOperand() const;
    void SetLeftOperand(BaseComponent* value);
    //@}

    /// Gets or sets the comparison operator
    //@{
    ComparisonConditionType GetOperator() const;
    void SetOperator(ComparisonConditionType value);
    //@}

    /// Gets or sets the right operand
    //@{
    BaseComponent* GetRightOperand() const;
    void SetRightOperand(BaseComponent* value);
    //@}

    /// Method that evaluates the condition. This method will return false if the operator is
    /// incompatible with the operand types. For instance, operators *LessThan*, *LessThanOrEqual*,
    /// *GreaterThan* and *GreaterThanOrEqual* require both operands to be comparable
    bool Evaluate() const;

public:
    static const DependencyProperty* LeftOperandProperty;
    static const DependencyProperty* OperatorProperty;
    static const DependencyProperty* RightOperandProperty;

protected:
    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

private:
    void EnsureBindingValues() const;
    void EnsureOperands() const;

private:
    mutable const Type* mSourceType;
    mutable Ptr<TypeConverter> mConverter;
    mutable Ptr<BaseComponent> mLeft;
    mutable Ptr<BaseComponent> mRight;
    mutable Ptr<ComparisonLogic> mComparator;

    NS_DECLARE_REFLECTION(ComparisonCondition, Animatable)
};

NS_WARNING_POP

}

NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_INTERACTIVITY_API, Noesis::ComparisonConditionType)


#endif
