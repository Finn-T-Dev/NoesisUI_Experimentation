////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMPONENT_H__
#define __GUI_COMPONENT_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Decorator.h>


namespace Noesis
{
struct Uri;
template<class T> class UICollection;
struct NotifyCollectionChangedEventArgs;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Types of dynamic properties supported
////////////////////////////////////////////////////////////////////////////////////////////////////
enum DynamicPropertyType
{
    DynamicPropertyType_Bool,
    DynamicPropertyType_Integer,
    DynamicPropertyType_Float,
    DynamicPropertyType_String,
    DynamicPropertyType_Image,
    DynamicPropertyType_Brush,
    DynamicPropertyType_Object
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a custom property that will be automatically registered in the Component classs
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DynamicProperty: public DependencyObject
{
public:
    DynamicProperty();
    ~DynamicProperty();

    /// Gets or sets the property name
    //@{
    const char* GetName() const;
    void SetName(const char* value);
    //@}

    /// Gets or sets the property type
    //@{
    DynamicPropertyType GetType() const;
    void SetType(DynamicPropertyType value);
    //@}

    /// Gets or sets the default value for the property
    //@{
    const char* GetDefaultValue() const;
    void SetDefaultValue(const char* value);
    //@}

public:
    static const DependencyProperty* NameProperty;
    static const DependencyProperty* TypeProperty;
    static const DependencyProperty* DefaultValueProperty;

private:
    NS_DECLARE_REFLECTION(DynamicProperty, DependencyObject)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef UICollection<DynamicProperty> DynamicPropertyCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a user control that can be extended with custom properties
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Component: public Decorator
{
public:
    Component();
    Component(const Uri& source);
    ~Component();

    /// Gets or sets the source file for this component
    //@{
    const Uri& GetSource() const;
    void SetSource(const Uri& value);
    //@}

    /// Gets or sets the list of dynamic properties defined in this component
    //@{
    DynamicPropertyCollection* GetDynamicProperties() const;
    //@}

    /// Registers a dynamic property in the Component reflection type
    static void RegisterProperty(const char* propName, DynamicPropertyType propType,
        const char* defaultValue);

    /// Releases dynamic properties default values
    static void Shutdown();

    // From FrameworkElement
    //@{
    FrameworkElement* GetStateGroupsRoot() const override;
    //@}

public:
    static const DependencyProperty* SourceProperty;

private:
    void OnPropsChanged(BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& e);

    void OnPropertyChanges(BaseComponent* d, const DependencyPropertyChangedEventArgs& e);

    void RegisterChanges();
    void UnregisterChanges();
    void RegisterChanges(DynamicProperty* prop);
    void UnregisterChanges(DynamicProperty* prop);

    void RegisterProperty(DynamicProperty* prop);

    void LoadSource(const Uri& source);

private:
    Ptr<DynamicPropertyCollection> mDynamicProperties;

    NS_DECLARE_REFLECTION(Component, Decorator)
};

NS_WARNING_POP

}

NS_DECLARE_REFLECTION_ENUM(Noesis::DynamicPropertyType)

#endif
