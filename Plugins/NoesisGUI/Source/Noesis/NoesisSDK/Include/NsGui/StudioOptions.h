////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STUDIOOPTIONS_H__
#define __GUI_STUDIOOPTIONS_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsCore/Ptr.h>
#include <NsGui/XamlProvider.h>
#include <NsGui/FontProvider.h>
#include <NsGui/TextureProvider.h>
#include <NsGui/Uri.h>


namespace Noesis
{
namespace Studio
{

struct Options
{
    template<class T> using Ptr = Noesis::Ptr<T>;
    template<class T> using Delegate = Noesis::Delegate<T>;

    // Invoked to provide a XAML provider located at the specified path for the given assembly
    Delegate<Ptr<Noesis::XamlProvider>(const char* assembly, const char* path)> GetXamlProvider;

    // Invoked to provide a Texture provider located at the specified path for the given assembly
    Delegate<Ptr<Noesis::TextureProvider>(const char* assembly, const char* path)> GetTextureProvider;

    // Invoked to provide a Font provider located at the specified path for the given assembly
    Delegate<Ptr<Noesis::FontProvider>(const char* assembly, const char* path)> GetFontProvider;

    // Invoked when a new assembly is registered
    Delegate<void (const char* assembly, const char* path)> RegisterAssembly;

    // Invoked when a new file is created by Studio
    Delegate<void (const Uri& uri)> FileCreated;

    // Invoked when an existing file is modified by Studio
    Delegate<void (const Uri& uri)> FileWritten;

    // Invoked when a file is moved or renamed by Studio
    Delegate<void (const Uri& src, const Uri& dst)> FileMoved;

    // Invoked when the save state of the project changes
    Delegate<void (bool hasUnsavedChanges)> SaveStateChanged;

    // Invoked when Studio requests to close
    Delegate<void ()> Exit;

    // Handle to the parent window in which Studio is embedded
    void* parentWindow = 0;
};

}
}

#endif
