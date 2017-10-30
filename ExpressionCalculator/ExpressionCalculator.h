// ExpressionCalculator.h

#pragma once

#define DLLEXPORT extern "C" __declspec(dllexport)

DLLEXPORT double Calculate(char* inputExpression, const bool angularMeasure);