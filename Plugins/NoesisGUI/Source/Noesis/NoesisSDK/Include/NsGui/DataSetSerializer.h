////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DATASETSERIALIZER_H__
#define __GUI_DATASETSERIALIZER_H__


#include <NsCore/Noesis.h>
#include <NsCore/Nullable.h>
#include <NsCore/StringFwd.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{

class BaseComponent;

/// Sets the default culture
NS_GUI_CORE_API void SerializeDataSet(const BaseComponent* input, BaseString& output,
    uint32_t indentWidth = 2, char indentType = ' ', Nullable<uint32_t> wrapWidth = nullptr, bool isCrlf = true);

}


#endif
