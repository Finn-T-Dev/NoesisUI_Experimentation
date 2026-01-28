////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MathConverter.h"
#include "ArithmeticParser.h"

#include <NsCore/ReflectionImplement.h>
#include <NsCore/StringUtils.h>

#ifdef NS_HAVE_STUDIO
#include <NsCore/Category.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::MathConverter::MathConverter(): mExpr("{0}")
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::MathConverter::GetExpression() const
{
    return mExpr.Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::MathConverter::SetExpression(const char* expr)
{
    mExpr = expr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::MathConverter::TryConvert(BaseComponent* value, const Noesis::Type*, BaseComponent* parameter,
    Noesis::Ptr<BaseComponent>& result)
{
    if (!mExpr.Empty())
    {
        uint32_t charParsed;
        float input = value ? Noesis::StrToFloat(value->ToString().Str(), &charParsed) : 0.0f;
        float param = parameter ? Noesis::StrToFloat(parameter->ToString().Str(), &charParsed) : 0.0f;
        float output;

        if (Parse(mExpr.Str(), input, param, output))
        {
            result.Reset(Noesis::Boxing::Box(output));
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::MathConverter::TryConvert(Noesis::ArrayRef<BaseComponent*> values,
    const Noesis::Type* targetType, BaseComponent* parameter, Noesis::Ptr<BaseComponent>& result)
{
    if (!mExpr.Empty())
    {
        uint32_t charParsed;
        Noesis::Vector<float, 8> inputs;
        for (uint32_t i = 0; i < values.Size(); ++i)
        {
            inputs.PushBack(values[i] ? Noesis::StrToFloat(values[i]->ToString().Str(), &charParsed)
                : 0.0f);
        }
        float param = parameter ? Noesis::StrToFloat(parameter->ToString().Str(), &charParsed)
            : 0.0f;
        float output;

        if (Parse(mExpr.Str(), inputs, param, output))
        {
            // No automatic conversion in MultiBindings, so we have to check the target type
            if (targetType == Noesis::TypeOf<float>())
            {
                result.Reset(Noesis::Boxing::Box(output));
                return true;
            }
            if (targetType == Noesis::TypeOf<int>())
            {
                result.Reset(Noesis::Boxing::Box((int)output));
                return true;
            }
            if (targetType == Noesis::TypeOf<Noesis::String>())
            {
                result.Reset(Noesis::Boxing::Box(Noesis::ToString(output)));
                return true;
            }
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::MathConverter::TryConvertBack(BaseComponent*, Noesis::ArrayRef<const Noesis::Type*>,
    BaseComponent*, Noesis::BaseVector<Noesis::Ptr<BaseComponent>>&)
{
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::MathConverter, "NoesisGUIExtensions.MathConverter")
{
  #ifdef NS_HAVE_STUDIO
    NsMeta<Noesis::Category>("Converters");
  #endif

    NsImpl<IMultiValueConverter>();

    NsProp("Expression", &NoesisApp::MathConverter::mExpr);
}

NS_END_COLD_REGION
