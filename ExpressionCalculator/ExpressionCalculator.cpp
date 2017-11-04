// ExpressionCalculator.cpp

#include "ExpressionCalculator.h"

#define _USE_MATH_DEFINES

#include <string>
#include <cmath>

using std::string;

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

bool IsArithmeticOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int ArithmeticOperatorPriority(char c)
{
	if (c == '+' || c == '-')
	{
		return 0;
	}
	if (c == '*' || c == '/')
	{
		return 1;
	}
	return 2;
}

bool IsFunction(string s)
{
	return s == "sqrt" || s == "cbrt" || s == "log" || s == "ln" || s == "exp" || s == "fact"
		|| s == "sin" || s == "cos" || s == "tan" || s == "asin" || s == "acos" || s == "atan"
		|| s == "sinh" || s == "cosh" || s == "tanh" || s == "asinh" || s == "acosh" || s == "atanh";
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

Node* BuildExpressionTree(string expression)
{
	DeleteUnnecessarySideBrackets(expression);

	if (expression == "")
	{
		return nullptr;
	}

	string function = "";
	int minPriority = 3;
	int minPriorityOperationIndex = 0;
	int minPriorityOperationLength = 0;
	int bracketCount = 0;
	for (size_t i = 0; i < expression.length(); i++)
	{
		if (IsArithmeticOperator(expression[i])
			&& ArithmeticOperatorPriority(expression[i]) <= minPriority && !bracketCount)
		{
			minPriority = ArithmeticOperatorPriority(expression[i]);
			minPriorityOperationIndex = i;
			minPriorityOperationLength = 1;
		}
		else if (isalpha(expression[i]) && minPriority == 3)
		{
			function += expression[i];

			if (!isalpha(expression[i + 1]) && IsFunction(function))
			{
				if (!bracketCount)
				{
					minPriorityOperationIndex = i;
					minPriorityOperationLength = function.length();
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

	if (!minPriorityOperationIndex && isdigit(expression[0]))
	{
		return NewNode(expression);
	}

	Node* node = NewNode(expression.substr(
		minPriorityOperationIndex - minPriorityOperationLength + 1, minPriorityOperationLength));

	node->left = BuildExpressionTree(expression.substr(
		0, minPriorityOperationIndex - minPriorityOperationLength + 1));
	node->right = BuildExpressionTree(expression.substr(minPriorityOperationIndex + 1));

	return node;
}

// 0 - DEG, 1 - RAD
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