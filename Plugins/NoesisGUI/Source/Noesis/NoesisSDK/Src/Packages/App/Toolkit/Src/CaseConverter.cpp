////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "CaseConverter.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>

#ifdef NS_HAVE_STUDIO
#include <NsCore/Category.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
static char CaseConverterToUpper(char c)
{
    return (c >= 'a' && c <= 'z') ? (c - ('a' - 'A')) : c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static char CaseConverterToLower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::CaseConverter::CaseConverter() : mFormat(CaseFormat_UpperCase)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::CaseConverter::TryConvert(Noesis::BaseComponent* value, const Noesis::Type*,
    Noesis::BaseComponent*, Noesis::Ptr<Noesis::BaseComponent>& result)
{
    if (value != nullptr)
    {
        Noesis::String in = value->ToString();

        if (!in.Empty())
        {
            uint32_t numChars = in.Size();

            Noesis::String out;
            out.Resize(numChars);

            switch (mFormat)
            {
                case CaseFormat_UpperCase:
                {
                    for (uint32_t i = 0; i < numChars; i++)
                    {
                        out[i] = CaseConverterToUpper(in[i]);
                    }
                    break;
                }
                case CaseFormat_LowerCase:
                {
                    for (uint32_t i = 0; i < numChars; i++)
                    {
                        out[i] = CaseConverterToLower(in[i]);
                    }
                    break;
                }
                default:
                    NS_ASSERT_UNREACHABLE;
            }

            result.Reset(Noesis::Boxing::Box(out));
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::CaseFormat NoesisApp::CaseConverter::GetFormat() const
{
    return mFormat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::CaseConverter::SetFormat(CaseFormat format)
{
    mFormat = format;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::CaseConverter, "NoesisGUIExtensions.CaseConverter")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<Noesis::Category>("Converters");
  #endif

    NsProp("Format", &NoesisApp::CaseConverter::GetFormat, &NoesisApp::CaseConverter::SetFormat);
}

NS_IMPLEMENT_REFLECTION_ENUM(NoesisApp::CaseFormat, "NoesisGUIExtensions.CaseFormat")
{
    NsVal("LowerCase", NoesisApp::CaseFormat_LowerCase);
    NsVal("UpperCase", NoesisApp::CaseFormat_UpperCase);
}

NS_END_COLD_REGION
