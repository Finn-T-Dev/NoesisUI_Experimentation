////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_CASECONVERTER_H__
#define __APP_CASECONVERTER_H__


#include <NsCore/Noesis.h>
#include <NsCore/String.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/BaseValueConverter.h>


namespace NoesisApp
{
////////////////////////////////////////////////////////////////////////////////////////////////////
enum CaseFormat
{
    CaseFormat_UpperCase,
    CaseFormat_LowerCase,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class CaseConverter final : public Noesis::BaseValueConverter
{
public:
    CaseConverter();

    bool TryConvert(Noesis::BaseComponent* value, const Noesis::Type* targetType,
        Noesis::BaseComponent* parameter, Noesis::Ptr<Noesis::BaseComponent>& result) final;

    CaseFormat GetFormat() const;
    void SetFormat(CaseFormat format);

private:
    CaseFormat mFormat;

    NS_DECLARE_REFLECTION(CaseConverter, BaseValueConverter)
};

}

NS_DECLARE_REFLECTION_ENUM(NoesisApp::CaseFormat)

#endif
