////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_ARITHMETICPARSER_H__
#define __APP_ARITHMETICPARSER_H__


#include <NsCore/ArrayRef.h>


// Evaluates the mathematical expression, substituting the provided input values for any variables
// in the expression. Variables in the expression are expected to be in the form {N}, where N is
// the index of the corresponding input value in the inputs array. {_} is used for the float param
bool Parse(const char* expr, Noesis::ArrayRef<float> inputs, float param, float& value);

#endif
