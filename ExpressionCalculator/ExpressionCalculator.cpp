// ExpressionCalculator.cpp

#include "ExpressionCalculator.h"

#define _USE_MATH_DEFINES

#include <string>
#include <cmath>

using std::string;

bool IsBracket(char c)
{
	return c == '(' || c == ')';
}

bool IsArithmeticOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool IsFunction(string s)
{
	return s == "sqrt" || s == "cbrt" || s == "log" || s == "ln" || s == "exp" || s == "fact"
		|| s == "sin" || s == "cos" || s == "tan" || s == "asin" || s == "acos" || s == "atan"
		|| s == "sinh" || s == "cosh" || s == "tanh" || s == "asinh" || s == "acosh" || s == "atanh";
}

int OperationPriority(string s)
{
	if (s == "+" || s == "-")
	{
		return 0;
	}
	if (s == "*" || s == "/")
	{
		return 1;
	}
	if (s == "^")
	{
		return 2;
	}
	return 3;
}

void DeleteUnnecessarySideBrackets(string& expression)
{
	bool sideBracketsMustBeDeleted = 1;
	while (expression[0] == '(' && expression[expression.length() - 1] == ')' && sideBracketsMustBeDeleted)
	{
		int bracketCount = 0;
		for (size_t i = 0; i < expression.length() && sideBracketsMustBeDeleted; i++)
		{
			if (IsArithmeticOperator(expression[i]) && !bracketCount)
			{
				sideBracketsMustBeDeleted = 0;
			}
			else if (expression[i] == '(')
			{
				bracketCount++;
			}
			else if (expression[i] == ')')
			{
				bracketCount--;
			}
		}

		if (sideBracketsMustBeDeleted)
		{
			expression.erase(0, 1);
			expression.erase(expression.length() - 1, 1);
		}
	}
}

struct Node
{
	string value;
	Node* left;
	Node* right;

	~Node()
	{
		delete left;
		delete right;
	}
};

Node* NewNode(string value)
{
	Node* temp = new Node;

	temp->value = value;
	temp->left = temp->right = nullptr;

	return temp;
}

Node* BuildExpressionTree(string expression)
{
	DeleteUnnecessarySideBrackets(expression);

	if (expression == "")
	{
		return nullptr;
	}

	string function = "";
	int minPriority = 3;
	int minPriorityOperatorIndex = 0;
	int minPriorityOperatorLength = 0;
	int bracketCount = 0;
	for (size_t i = 0; i < expression.length(); i++)
	{
		if (IsArithmeticOperator(expression[i])
			&& OperationPriority(string(1, expression[i])) <= minPriority && !bracketCount)
		{
			minPriority = OperationPriority(string(1, expression[i]));
			minPriorityOperatorIndex = i;
			minPriorityOperatorLength = 1;
		}
		else if (minPriority == 3 && isalpha(expression[i]))
		{
			function += expression[i];

			if (!isalpha(expression[i + 1]) && IsFunction(function))
			{
				if (OperationPriority(function) <= minPriority && !bracketCount)
				{
					minPriority = OperationPriority(function);
					minPriorityOperatorIndex = i;
					minPriorityOperatorLength = function.length();
				}

				function = "";
			}
		}
		else if (expression[i] == '(')
		{
			bracketCount++;
		}
		else if (expression[i] == ')')
		{
			bracketCount--;
		}
	}

	if (!minPriorityOperatorIndex && isdigit(expression[0]))
	{
		return NewNode(expression);
	}

	Node* node = NewNode(expression.substr(
		minPriorityOperatorIndex - minPriorityOperatorLength + 1, minPriorityOperatorLength));

	node->left = BuildExpressionTree(expression.substr(
		0, minPriorityOperatorIndex - minPriorityOperatorLength + 1));
	node->right = BuildExpressionTree(expression.substr(minPriorityOperatorIndex + 1));

	return node;
}

bool g_angularMeasure;

double PerformOperation(double operand1, double operand2, string operation)
{
	if (operation == "+")
	{
		return operand1 + operand2;
	}
	if (operation == "-")
	{
		return operand1 - operand2;
	}
	if (operation == "*")
	{
		return operand1 * operand2;
	}
	if (operation == "/")
	{
		return operand1 / operand2;
	}
	if (operation == "^")
	{
		return pow(operand1, operand2);
	}
	if (operation == "sqrt")
	{
		return sqrt(operand2);
	}
	if (operation == "cbrt")
	{
		return cbrt(operand2);
	}
	if (operation == "log")
	{
		return log10(operand2);
	}
	if (operation == "ln")
	{
		return log(operand2);
	}
	if (operation == "exp")
	{
		return exp(operand2);
	}
	if (operation == "fact")
	{
		return tgamma(operand2 + 1.0);
	}
	if (operation == "sin")
	{
		return g_angularMeasure ? sin(operand2) : sin(operand2 * M_PI / 180.0);
	}
	if (operation == "cos")
	{
		return g_angularMeasure ? cos(operand2) : cos(operand2 * M_PI / 180.0);
	}
	if (operation == "tan")
	{
		return g_angularMeasure ? tan(operand2) : tan(operand2 * M_PI / 180.0);
	}
	if (operation == "asin")
	{
		return g_angularMeasure ? asin(operand2) : asin(operand2) * 180.0 / M_PI;
	}
	if (operation == "acos")
	{
		return g_angularMeasure ? acos(operand2) : acos(operand2) * 180.0 / M_PI;
	}
	if (operation == "atan")
	{
		return g_angularMeasure ? atan(operand2) : atan(operand2) * 180.0 / M_PI;
	}
	if (operation == "sinh")
	{
		return sinh(operand2);
	}
	if (operation == "cosh")
	{
		return cosh(operand2);
	}
	if (operation == "tanh")
	{
		return tanh(operand2);
	}
	if (operation == "asinh")
	{
		return asinh(operand2);
	}
	if (operation == "acosh")
	{
		return acosh(operand2);
	}
	if (operation == "atanh")
	{
		return atanh(operand2);
	}
	return 0;
}

double CalculateExpression(Node* root)
{
	if (!root)
	{
		return 0;
	}

	if (!root->left && !root->right)
	{
		return atof(root->value.c_str());
	}

	double leftValue = CalculateExpression(root->left);
	double rightValue = CalculateExpression(root->right);

	return PerformOperation(leftValue, rightValue, root->value);
}

double Calculate(char* inputExpression, const bool angularMeasure)
{
	string expression(inputExpression);
	Node* root = BuildExpressionTree(expression);

	g_angularMeasure = angularMeasure;

	double result = CalculateExpression(root);

	delete root;

	return result;
}