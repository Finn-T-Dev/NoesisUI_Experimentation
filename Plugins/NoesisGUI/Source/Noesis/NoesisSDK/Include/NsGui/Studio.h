////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STUDIO_H__
#define __GUI_STUDIO_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsGui/StudioApi.h>
#include <NsGui/StudioOptions.h>


namespace Noesis
{

class FrameworkElement;

namespace Studio
{

/// Load a Studio project from the given project file and create its visual tree
NS_GUI_STUDIO_API Ptr<FrameworkElement> Create(const char* projectPath, const Options& options);

/// Save all unsaved changes made in the given Studio project
NS_GUI_STUDIO_API void SaveAllChanges(FrameworkElement* studio);

/// Discard all unsaved changes made in the given Studio project
NS_GUI_STUDIO_API void DiscardAllChanges(FrameworkElement* studio);

/// Request Studio to open a file if it exists in the project
NS_GUI_STUDIO_API bool OpenProjectFile(FrameworkElement* studio, const char* path);

/// Clear Studio's type cache
NS_GUI_STUDIO_API void ClearTypeCache();

/// Populate Studio's type cache
NS_GUI_STUDIO_API void PopulateTypeCache();

}

}

#endif
