// ExpressionCalculator.h

#pragma once

// param a Math expression.
// param b Angular measure (0 - DEG, 1 - RAD).
// return Result of math expression.
extern "C" __declspec(dllexport) double Calculate(char* inputExpression, const bool angularMeasure);