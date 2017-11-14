### Operations priority
Priority|Operation
-|-
1|+<br />-
2|*<br />/
3|^
4|sqrt()<br />cbrt()<br />log()<br />ln()<br />exp()<br />fact()<br />sin()<br />cos()<br />tan()<br />asin()<br />acos()<br />atan()<br />sinh()<br />cosh()<br />tanh()<br />asinh()<br />acosh()<br />atanh()
### How to use in C#
#### Import
[DllImport(@"ExpressionCalculator.dll", CallingConvention = CallingConvention.Cdecl)]  
static extern double Calculate(string expression, bool angularMeasure);
#### Annotation
angularMeasure (0 - DEG, 1 - RAD)
