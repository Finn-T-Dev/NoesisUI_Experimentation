////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STUDIOMETA_H__
#define __GUI_STUDIOMETA_H__


#include <NsCore/Noesis.h>
#include <NsCore/Symbol.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/ArrayRef.h>
#include <NsCore/Type.h>
#include <NsCore/ArrayRef.h>
#include <NsGui/Uri.h>


#ifdef NS_HAVE_STUDIO


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioProp: public TypeMetaData
{
public:
    typedef BaseComponent* (*GetSourceCallback)(BaseComponent* instance);

    StudioProp(const char* prop): _prop(prop), _targetType(0), _callback(0) {}
    StudioProp(const char* prop, const TypeClass* targetType): _prop(prop), _targetType(targetType), _callback(0) {}
    StudioProp(const char* prop, GetSourceCallback callback): _prop(prop), _targetType(0), _callback(callback) {}

    const char* Property() const { return _prop; }
    const TypeClass* TargetType() const { return _targetType; }
    GetSourceCallback SourceCallback() const { return _callback; }

private:
    const char* _prop;
    const TypeClass* _targetType;
    GetSourceCallback _callback;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioProp, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioName: public TypeMetaData
{
public:
    StudioName(const char* name) : _name(name) {}

    const char* Name() const { return _name; }

private:
    const char* _name;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioName, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioDesc: public TypeMetaData
{
public:
    StudioDesc(const char* desc): _desc(desc) {}

    const char* Description() const { return _desc; }

private:
    const char* _desc;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioDesc, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioHelpUri: public TypeMetaData
{
public:
    StudioHelpUri(const char* uri): _uri(uri) {}

    const char* HelpUri() const { return _uri; }

private:
    const char* _uri;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioHelpUri, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioIcon: public TypeMetaData
{
public:
    StudioIcon(const Uri& font, uint32_t ch): _font(font), _ch(ch) {}

    const Uri& Font() const { return _font; }
    uint32_t Char() const { return _ch; }

private:
    Uri _font;
    uint32_t _ch;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioIcon, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioMin: public TypeMetaData
{
public:
    StudioMin(float min): _min(min) {}
    StudioMin(int32_t min): _min((float)min) {}

    float Min() const { return _min; }

private:
    float _min;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioMin, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioRange: public TypeMetaData
{
public:
    StudioRange(float min, float max): _min(min), _max(max) {}
    StudioRange(int32_t min, int32_t max): _min((float)min), _max((float)max) {}

    float Min() const { return _min; }
    float Max() const { return _max; }

private:
    float _min, _max;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioRange, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioOrder: public TypeMetaData
{
public:
    StudioOrder(int order): _order(order), _primary(true), _category("") {}
    StudioOrder(int order, const char* category): _order(order), _primary(true), _category(category) {}
    StudioOrder(int order, bool primary): _order(order), _primary(primary), _category("") {}
    StudioOrder(int order, bool primary, const char* category): _order(order), _primary(primary),
        _category(category) {}

    int Order() const { return _order; }
    bool Primary() const { return _primary; }
    const char* Category() const { return _category; }

private:
    int _order;
    bool _primary;
    const char* _category;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioOrder, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioRoot: public TypeMetaData
{
public:
    StudioRoot(const char* xaml): _xaml(xaml) {}

    const char* XAML() const { return _xaml; }

private:
    const char* _xaml;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioRoot, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioVisualStates: public TypeMetaData
{
public:
    struct Group
    {
        const char* name;
        const char* states[10];
    };

    StudioVisualStates(ArrayRef<StudioVisualStates::Group> groups)
    {
        uint32_t numGroups = groups.Size();
        _groups.Resize(numGroups);

        for (uint32_t i = 0; i < numGroups; i++)
        {
            _groups[i] = groups[i];
        }
    }

    ArrayRef<StudioVisualStates::Group> Groups() { return _groups; }

private:
    Noesis::Vector<StudioVisualStates::Group> _groups;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioVisualStates, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioTemplate: public TypeMetaData
{
public:
    StudioTemplate(const char* xaml): _xaml(xaml) {}

    const char* XAML() const { return _xaml; }

private:
    const char* _xaml;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioTemplate, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class StudioNavigatorProperty: public TypeMetaData
{
public:
    StudioNavigatorProperty() = default;

    NS_IMPLEMENT_INLINE_REFLECTION_(StudioNavigatorProperty, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ItemType: public TypeMetaData
{
public:
    ItemType(const Type* type): _type(type) {}

    const Type* Type() { return _type; }

private:
    const Noesis::Type* _type;

    NS_IMPLEMENT_INLINE_REFLECTION_(ItemType, TypeMetaData)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Attach: public TypeMetaData
{
public:
    Attach(const char* name): _name(Symbol::Static(name)) {}

    template<typename... Types>
    Attach* To()
    {
        TypeList<Types...>::Get(_toTypes);
        return this;
    }

    template<typename... Types>
    Attach* On()
    {
        TypeList<Types...>::Get(_onTypes);
        return this;
    }

    template<class T, class... Args>
    Attach* Meta(Args&&... args)
    {
        Ptr<T> meta = *new T(ForwardArg<Args>(args)...);
        _metadatas.PushBack(meta);
        return this;
    }

    Symbol Name() { return _name; }
    ArrayRef<const Type*> ToTypes() { return _toTypes; }
    ArrayRef<const Type*> OnTypes() { return _onTypes; }
    ArrayRef<Ptr<TypeMetaData>> Metas() { return _metadatas; }

private:
    template<typename... Types> struct CountTypes;

    template<> struct CountTypes<>
    {
        constexpr static uint32_t Size = 0;
    };

    template<typename T, typename... Types> struct CountTypes<T, Types...>
    {
        constexpr static uint32_t Size = 1 + CountBytes<Types...>::Size;
    };

    template<typename... Types> struct TypeList;

    template<>
    struct TypeList<>
    {
        static void Get(Vector<const Type*>&) {}
    };

    template<typename T, typename... Types>
    struct TypeList<T, Types...>
    {
        static void Get(Vector<const Type*>& v)
        {
            v.Reserve(CountTypes<Types...>::Size);
            v.PushBack(TypeOf<T>());
            TypeList<Types...>::Get(v);
        }
    };

private:
    Symbol _name;
    Vector<const Type*> _toTypes;
    Vector<const Type*> _onTypes;
    Vector<Ptr<TypeMetaData>> _metadatas;

    NS_IMPLEMENT_INLINE_REFLECTION_(Attach, TypeMetaData)
};

}

#endif

#endif
