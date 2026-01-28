////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/DynamicKeyTemplateSelector.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/Nullable.h>
#include <NsGui/DataTemplate.h>
#include <NsGui/DependencyProperty.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::DynamicKeyTemplateSelector::DynamicKeyTemplateSelector() : mUseItemTypeName(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::DataTemplate* NoesisApp::DynamicKeyTemplateSelector::SelectTemplate(BaseComponent* item,
    Noesis::DependencyObject*)
{
    NS_CHECK(!mKeyStringFormat.Empty(), "KeyStringFormat is empty");
    if (item == nullptr)
    {
        return nullptr;
    }

    Noesis::String baseKey;
    if (mUseItemTypeName)
    {
        // Remove type namespace from key
        const char* typeName = item->GetClassType()->GetName();
        int periodPos = Noesis::StrFindFirst(typeName, ".");
        if (periodPos != -1)
        {
            typeName += periodPos + 1;
        }
        baseKey.Assign(typeName);
    }
    else if (Noesis::Boxing::CanUnbox<Noesis::String>(item))
    {
        baseKey.Assign(Noesis::Boxing::Unbox<Noesis::String>(item));
        if (Noesis::StrEquals(baseKey.Str(), "True"))
        {
            baseKey.Assign(mBooleanTrueValue.Str());
        }
        else if (Noesis::StrEquals(baseKey.Str(), "False"))
        {
            baseKey.Assign(mBooleanFalseValue.Str());
        }
    }
    else if (Noesis::Boxing::CanUnbox<int8_t>(item))
    {
        baseKey.Assign(Noesis::String(Noesis::String::VarArgs(), "%d",
            Noesis::Boxing::Unbox<int8_t>(item)));
    }
    else if (Noesis::Boxing::CanUnbox<int16_t>(item))
    {
        baseKey.Assign(Noesis::String(Noesis::String::VarArgs(), "%d",
            Noesis::Boxing::Unbox<int16_t>(item)));
    }
    else if (Noesis::Boxing::CanUnbox<int32_t>(item))
    {
        baseKey.Assign(Noesis::String(Noesis::String::VarArgs(), "%d",
            Noesis::Boxing::Unbox<int32_t>(item)));
    }
    else if (Noesis::Boxing::CanUnbox<uint8_t>(item))
    {
        baseKey.Assign(Noesis::String(Noesis::String::VarArgs(), "%d",
            Noesis::Boxing::Unbox<uint8_t>(item)));
    }
    else if (Noesis::Boxing::CanUnbox<uint16_t>(item))
    {
        baseKey.Assign(Noesis::String(Noesis::String::VarArgs(), "%d",
            Noesis::Boxing::Unbox<uint16_t>(item)));
    }
    else if (Noesis::Boxing::CanUnbox<uint32_t>(item))
    {
        baseKey.Assign(Noesis::String(Noesis::String::VarArgs(), "%d",
            Noesis::Boxing::Unbox<uint32_t>(item)));
    }
    else if (Noesis::Boxing::CanUnbox<float>(item))
    {
        baseKey.Assign(Noesis::String(Noesis::String::VarArgs(), "%.0f",
            Noesis::Boxing::Unbox<float>(item)));
    }
    else if (Noesis::Boxing::CanUnbox<bool>(item))
    {
        baseKey.Assign(Noesis::Boxing::Unbox<bool>(item) ? mBooleanTrueValue.Str()
            : mBooleanFalseValue.Str());
    }
    else
    {
        return nullptr;
    }

    Noesis::String key(Noesis::String::VarArgs(), mKeyStringFormat.Str(), baseKey.Str());
    BaseComponent* resource = FindNodeResource(key.Str(), false);

    if (resource == nullptr || nullptr == Noesis::DependencyProperty::GetUnsetValue())
    {
        return nullptr;
    }

    return Noesis::DynamicCast<Noesis::DataTemplate*>(resource);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::DynamicKeyTemplateSelector::GetUseItemTypeName() const
{
    return mUseItemTypeName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DynamicKeyTemplateSelector::SetUseItemTypeName(bool value)
{
    mUseItemTypeName = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::DynamicKeyTemplateSelector::GetKeyStringFormat() const
{
    return mKeyStringFormat.Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DynamicKeyTemplateSelector::SetKeyStringFormat(const char* value)
{
    mKeyStringFormat.Assign(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::DynamicKeyTemplateSelector::GetBooleanTrueValue() const
{
    return mBooleanTrueValue.Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DynamicKeyTemplateSelector::SetBooleanTrueValue(const char* value)
{
    mBooleanTrueValue.Assign(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::DynamicKeyTemplateSelector::GetBooleanFalseValue() const
{
    return mBooleanFalseValue.Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DynamicKeyTemplateSelector::SetBooleanFalseValue(const char* value)
{
    mBooleanFalseValue.Assign(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::DynamicKeyTemplateSelector,
    "NoesisGUIExtensions.DynamicKeyTemplateSelector")
{
    NsProp("UseItemTypeName", &NoesisApp::DynamicKeyTemplateSelector::GetUseItemTypeName,
        &NoesisApp::DynamicKeyTemplateSelector::SetUseItemTypeName);
    NsProp("KeyStringFormat", &NoesisApp::DynamicKeyTemplateSelector::GetKeyStringFormat,
        &NoesisApp::DynamicKeyTemplateSelector::SetKeyStringFormat);
    NsProp("BooleanTrueValue", &NoesisApp::DynamicKeyTemplateSelector::GetBooleanTrueValue,
        &NoesisApp::DynamicKeyTemplateSelector::SetBooleanTrueValue);
    NsProp("BooleanFalseValue", &NoesisApp::DynamicKeyTemplateSelector::GetBooleanFalseValue,
        &NoesisApp::DynamicKeyTemplateSelector::SetBooleanFalseValue);
}

NS_END_COLD_REGION
