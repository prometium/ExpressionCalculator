// ExpressionCalculator.h

#pragma once

// param expression Math expression.
// param angularMeasure Angular measure (0 - DEG, 1 - RAD).
// return Result of math expression.
extern "C" __declspec(dllexport) double Calculate(char* expression, const bool angularMeasure);