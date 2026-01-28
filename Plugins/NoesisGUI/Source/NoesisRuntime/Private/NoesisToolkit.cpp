////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4426)
#endif


// TODO:
// Can't include App.Toolkit.cpp because yet because it uses EmbeddedProviders for default styles and fonts
//#include "NoesisSDK/Src/Packages/App/Toolkit/Src/App.Toolkit.cpp"
// So we just copy the parts we need for now
//@{

#include <NsCore/Package.h>
#include <NsCore/EnumConverter.h>

#include "NoesisSDK/Src/Packages/App/Toolkit/Src/MathConverter.h"
#include "NoesisSDK/Src/Packages/App/Toolkit/Src/CaseConverter.h"
#include "NoesisSDK/Src/Packages/App/Toolkit/Src/ThicknessConverter.h"


NS_BEGIN_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_REGISTER_REFLECTION(App, Toolkit)
{
    NS_REGISTER_COMPONENT(NoesisApp::MathConverter)
    NS_REGISTER_COMPONENT(NoesisApp::CaseConverter)
    NS_REGISTER_COMPONENT(NoesisApp::ThicknessConverter)

    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::CaseFormat>)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::ThicknessFormat>)
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INIT_PACKAGE(App, Toolkit)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_SHUTDOWN_PACKAGE(App, Toolkit)
{
}

NS_END_COLD_REGION

//@}

#include "NoesisSDK/Src/Packages/App/Toolkit/Src/ArithmeticParser.cpp"
#include "NoesisSDK/Src/Packages/App/Toolkit/Src/MathConverter.cpp"
#include "NoesisSDK/Src/Packages/App/Toolkit/Src/CaseConverter.cpp"
#include "NoesisSDK/Src/Packages/App/Toolkit/Src/ThicknessConverter.Toolkit.cpp"

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
