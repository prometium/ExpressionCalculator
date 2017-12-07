### Operations priority
Priority|Operation
-|-
1|sqrt()<br />cbrt()<br />log()<br />ln()<br />exp()<br />fact()<br />sin()<br />cos()<br />tan()<br />asin()<br />acos()<br />atan()<br />sinh()<br />cosh()<br />tanh()<br />asinh()<br />acosh()<br />atanh()
2|^
3|*<br />/
4|+<br />-
### How to use in C#
#### Import
[DllImport(@"ExpressionCalculator.dll", CallingConvention = CallingConvention.Cdecl)]  
static extern double Calculate(string expression, bool angularMeasure);
