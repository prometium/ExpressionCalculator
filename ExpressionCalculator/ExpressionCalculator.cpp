// ExpressionCalculator.cpp

#include "ExpressionCalculator.h"

#define _USE_MATH_DEFINES

#include <string>
#include <cmath>

using std::string;

bool IsNumber(char c)
{
	return '0' <= c && c <= '9';
}

bool IsBracket(char c)
{
	return c == '(' || c == ')';
}

bool IsOperation(string s)
{
	return s == "+" || s == "-" || s == "*" || s == "/" || s == "mod" || s == "^"
		|| s == "sqrt" || s == "cbrt" || s == "log" || s == "ln" || s == "exp" || s == "fact"
		|| s == "sin" || s == "cos" || s == "tan" || s == "asin" || s == "acos" || s == "atan"
		|| s == "sinh" || s == "cosh" || s == "tanh" || s == "asinh" || s == "acosh" || s == "atanh";
}

int OperationPriority(string s)
{
	if (s == "+" || s == "-")
	{
		return 0;
	}
	if (s == "*" || s == "/" || s == "mod")
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
		string operation = "";
		int bracketCount = 0;
		for (size_t i = 0; i < expression.length() && sideBracketsMustBeDeleted; i++)
		{
			if (!IsNumber(expression[i]) && expression[i] != '.' && !IsBracket(expression[i]))
			{
				operation += expression[i];

				if (IsOperation(operation) && !IsOperation(operation + expression[i + 1]))
				{
					if (!bracketCount)
					{
						sideBracketsMustBeDeleted = 0;
					}

					operation = "";
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

	string operation = "";
	int minPriority = 3;
	int minPriorityOperatorIndex = 0;
	int minPriorityOperatorLength = 0;
	int bracketCount = 0;
	for (size_t i = 0; i < expression.length(); i++)
	{
		if (!IsNumber(expression[i]) && expression[i] != '.' && !IsBracket(expression[i]))
		{
			operation += expression[i];

			if (IsOperation(operation) && !IsOperation(operation + expression[i + 1]))
			{
				if (OperationPriority(operation) <= minPriority && !bracketCount)
				{
					minPriority = OperationPriority(operation);
					minPriorityOperatorIndex = i;
					minPriorityOperatorLength = operation.length();
				}

				operation = "";
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

	if (!minPriorityOperatorIndex && IsNumber(expression[0]))
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

double PerformOperation(double operand1, double operand2, string operation, bool angularMeasure)
{
	enum { RAD, DEG };

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
	if (operation == "mod")
	{
		return fmod(operand1, operand2);
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
		return angularMeasure == RAD ? sin(operand2) : sin(operand2 * M_PI / 180.0);
	}
	if (operation == "cos")
	{
		return angularMeasure == RAD ? cos(operand2) : cos(operand2 * M_PI / 180.0);
	}
	if (operation == "tan")
	{
		return angularMeasure == RAD ? tan(operand2) : tan(operand2 * M_PI / 180.0);
	}
	if (operation == "asin")
	{
		return angularMeasure == RAD ? asin(operand2) : asin(operand2) * 180.0 / M_PI;
	}
	if (operation == "acos")
	{
		return angularMeasure == RAD ? acos(operand2) : acos(operand2) * 180.0 / M_PI;
	}
	if (operation == "atan")
	{
		return angularMeasure == RAD ? atan(operand2) : atan(operand2) * 180.0 / M_PI;
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

double CalculateExpression(Node* root, bool angularMeasure)
{
	if (!root)
	{
		return 0;
	}

	if (!root->left && !root->right)
	{
		return atof(root->value.c_str());
	}

	double leftValue = CalculateExpression(root->left, angularMeasure);
	double rightValue = CalculateExpression(root->right, angularMeasure);

	return PerformOperation(leftValue, rightValue, root->value, angularMeasure);
}

double Calculate(char* inputExpression, bool angularMeasure)
{
	string expression(inputExpression);
	Node* root = BuildExpressionTree(expression);

	double result = CalculateExpression(root, angularMeasure);

	delete root;

	return result;
}