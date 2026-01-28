////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MATHCONVERTER_H__
#define __APP_MATHCONVERTER_H__


#include <NsCore/Noesis.h>
#include <NsCore/String.h>
#include <NsGui/BaseValueConverter.h>
#include <NsGui/IMultiValueConverter.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class MathConverter final : public Noesis::BaseValueConverter, public Noesis::IMultiValueConverter
{
public:
    MathConverter();

    const char* GetExpression() const;
    void SetExpression(const char* expr);

    /// From IValueConverter
    //@{
    bool TryConvert(Noesis::BaseComponent* value, const Noesis::Type* targetType,
        Noesis::BaseComponent* parameter, Noesis::Ptr<Noesis::BaseComponent>& result) final;
    using BaseValueConverter::TryConvertBack;
    //@}

    /// From IMultiValueConverter
    //@{
    bool TryConvert(Noesis::ArrayRef<Noesis::BaseComponent*> values, const Noesis::Type* targetType,
        Noesis::BaseComponent* parameter, Noesis::Ptr<Noesis::BaseComponent>& result) override;
    bool TryConvertBack(Noesis::BaseComponent* value,
        Noesis::ArrayRef<const Noesis::Type*> targetTypes, Noesis::BaseComponent* parameter,
        Noesis::BaseVector<Noesis::Ptr<Noesis::BaseComponent>>& results) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    Noesis::String mExpr;

    NS_DECLARE_REFLECTION(MathConverter, BaseValueConverter)
};

}

#endif
