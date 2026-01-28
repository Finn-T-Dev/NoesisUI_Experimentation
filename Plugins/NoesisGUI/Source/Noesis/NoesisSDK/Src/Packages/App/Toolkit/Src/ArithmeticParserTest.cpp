////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/UnitTest.h>

#include "ArithmeticParser.h"


using namespace Noesis;


////////////////////////////////////////////////////////////////////////////////////////////////////
static float Parse(const char* expr)
{
    float v;
    NS_UNITTEST_CHECK(::Parse(expr, nullptr, 0.0f, v));
    return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float Parse2(const char* expr)
{
    Vector<float> inputs(2);
    inputs[0] = 10.0f;
    inputs[1] = 20.0f;

    float v;
    NS_UNITTEST_CHECK(::Parse(expr, inputs, 100.0f, v));
    return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
UNITTEST(ArithmeticParser)
{
    NS_UNITTEST_CHECK(Parse("0") == 0);
    NS_UNITTEST_CHECK(Parse("  0") == 0);
    NS_UNITTEST_CHECK(Parse("0  ") == 0);
    NS_UNITTEST_CHECK(Parse("  0  ") == 0);
    NS_UNITTEST_CHECK(Parse("3 + 4") == 7);
    NS_UNITTEST_CHECK(Parse("3 + 4 * (2 - 1)") == 7);
    NS_UNITTEST_CHECK(Parse("3 * 4") == 12);
    NS_UNITTEST_CHECK(Parse("3 * 4 + 8") == 20);
    NS_UNITTEST_CHECK(Parse("1 + 2 * 3 - 4") == 3);
    NS_UNITTEST_CHECK(Parse("(1 + 2)") == 3);
    NS_UNITTEST_CHECK(Parse("(1 + 2) * (3 + 4)") == 21);
    NS_UNITTEST_CHECK(Parse("3 + 4 * 256 / pow((5 - 3), pow(2, 3))") == 7);
    NS_UNITTEST_CHECK(Parse("250 % 100") == 50);
    NS_UNITTEST_CHECK(Parse("min(0,1)") == 0);
    NS_UNITTEST_CHECK(Parse("max(0,1)") == 1);
    NS_UNITTEST_CHECK(Parse("min(max(0, 0.5), 1)") == 0.5);
    NS_UNITTEST_CHECK(Parse("min(max(0, -1), 1)") == 0);
    NS_UNITTEST_CHECK(Parse("min(max(0, 2), 1)") == 1);
    NS_UNITTEST_CHECK(Parse("sin(0)") == 0);
    NS_UNITTEST_CHECK(Parse("cos(0)") == 1);
    NS_UNITTEST_CHECK(Parse("-5") == -5);
    NS_UNITTEST_CHECK(Parse("10 - 5") == 5);

    NS_UNITTEST_CHECK(Parse2("{0}") == 10);
    NS_UNITTEST_CHECK(Parse2("{0} + {1}") == 30);
    NS_UNITTEST_CHECK(Parse2("{_}") == 100);
}
