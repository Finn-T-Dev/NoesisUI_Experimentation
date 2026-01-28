////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Package.h>
#include <NsCore/EnumConverter.h>
#include <NsApp/RadialNeedle.h>
#include <NsApp/RadialTicks.h>
#include <NsApp/RadialNumbers.h>
#include <NsApp/RadialBorder.h>
#include <NsApp/RadialGauge.h>
#include <NsApp/Star.h>
#include <NsApp/RegularPolygon.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/DynamicKeyTemplateSelector.h>
#include <NsApp/LayoutScaler.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/ResourceDictionary.h>

#include "MathConverter.h"
#include "CaseConverter.h"
#include "ThicknessConverter.h"
#include "NineSliceImage.h"

#include "Toolkit.generic.xaml.bin.h"
#include "ToolkitIcons.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


static EmbeddedXaml gXamls[] =
{
    { "Toolkit.generic.xaml", Toolkit_generic_xaml },
};

static EmbeddedFont gFonts[] =
{
    { "", ToolkitIcons_ttf },
};


NS_BEGIN_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_REGISTER_REFLECTION(App, Toolkit)
{
    NS_REGISTER_COMPONENT(NoesisApp::RadialNeedle)
    NS_REGISTER_COMPONENT(NoesisApp::RadialTicks)
    NS_REGISTER_COMPONENT(NoesisApp::RadialNumbers)
    NS_REGISTER_COMPONENT(NoesisApp::RadialBorder)
    NS_REGISTER_COMPONENT(NoesisApp::RadialGauge)
    NS_REGISTER_COMPONENT(NoesisApp::Star)
    NS_REGISTER_COMPONENT(NoesisApp::RegularPolygon)
    NS_REGISTER_COMPONENT(NoesisApp::DynamicKeyTemplateSelector)
    NS_REGISTER_COMPONENT(NoesisApp::MathConverter)
    NS_REGISTER_COMPONENT(NoesisApp::CaseConverter)
    NS_REGISTER_COMPONENT(NoesisApp::ThicknessConverter)
    NS_REGISTER_COMPONENT(NoesisApp::NineSliceImage)
    NS_REGISTER_COMPONENT(NoesisApp::LayoutScaler)

    NS_REGISTER_COMPONENT(EnumConverter<NoesisApp::CaseFormat>)
    NS_REGISTER_COMPONENT(EnumConverter<NoesisApp::ThicknessFormat>)

    NS_REGISTER_TEST(ArithmeticParser);

    GUI::SetAssemblyXamlProvider("Toolkit", MakePtr<EmbeddedXamlProvider>(gXamls));
    GUI::SetAssemblyFontProvider("Toolkit", MakePtr<EmbeddedFontProvider>(gFonts));
    GUI::RegisterDefaultStyles(Uri::Pack("Toolkit", "Toolkit.generic.xaml"));
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
