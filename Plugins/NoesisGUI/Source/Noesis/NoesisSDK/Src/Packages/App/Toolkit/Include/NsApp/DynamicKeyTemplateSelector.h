////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __EDITOR_STRINGKEYTEMPLATESELECTOR_H__
#define __EDITOR_STRINGKEYTEMPLATESELECTOR_H__


#include <NsCore/Noesis.h>
#include <NsApp/ToolkitApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/String.h>
#include <NsGui/DataTemplateSelector.h>


namespace Noesis
{
class DataTemplate;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a way to select a DataTemplate from the element's resources, based on the data object
/// and a key string format
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_TOOLKIT_API DynamicKeyTemplateSelector : public Noesis::DataTemplateSelector
{
public:
    DynamicKeyTemplateSelector();

    Noesis::DataTemplate* SelectTemplate(BaseComponent* item, Noesis::DependencyObject* container) override;

    /// Gets or sets whether to use the data object item's type name, if false the item's value
    /// will be used
    //@{
    bool GetUseItemTypeName() const;
    void SetUseItemTypeName(bool value);
    //@}

    /// Gets or sets string format to use for the generated key
    //@{
    const char* GetKeyStringFormat() const;
    void SetKeyStringFormat(const char* value);
    //@}

    /// Gets or sets string to use as a value if the item is a bool and true
    //@{
    const char* GetBooleanTrueValue() const;
    void SetBooleanTrueValue(const char* value);
    //@}

    /// Gets or sets string to use as a value if the item is a bool and false
    //@{
    const char* GetBooleanFalseValue() const;
    void SetBooleanFalseValue(const char* value);
    //@}

private:
    bool mUseItemTypeName;
    Noesis::String mKeyStringFormat, mBooleanTrueValue, mBooleanFalseValue;

    NS_DECLARE_REFLECTION(DynamicKeyTemplateSelector, Noesis::DataTemplateSelector)
};

NS_WARNING_POP

}

#endif
