#include<iostream>
#include<stack>
#include<string>

const bool isDigit(const char& symbol)
{
	return symbol >= '0' && symbol <= '9';
}

const bool isLeftAssociative(const char& operation)
{
	return operation != '^';
}

const std::string polishNotation(const std::string& expr)
{
	std::stack<char> operators;
	std::string output;
	for (char symbol : expr)
	{
		if (isDigit(symbol))
		{
			output.push_back(symbol);
			continue;
		}

		if (symbol == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				output.push_back(operators.top());
				operators.pop();
			}
			operators.pop();
			continue;
		}

		if (isLeftAssociative(symbol))
		{
			if (symbol == '+' || symbol == '-')
			{
				while (!operators.empty() && operators.top() != '+' && operators.top() != '-' && operators.top() != '(')
				{
					output.push_back(operators.top());
					operators.pop();
				}
			}
		}

		operators.push(symbol);
	}
	while (!operators.empty())
	{
		output.push_back(operators.top());
		operators.pop();
	}
	return output;
}

const int calculate(const int& lvalue, const int& rvalue, char& operation)
{
	switch (operation)
	{
	case '+':
		return lvalue + rvalue;
	case '-':
		return lvalue - rvalue;
	case '*':
		return lvalue * rvalue;
	case '/':
		if (rvalue != 0)
			return lvalue / rvalue;
		throw("Cannot divide by 0!");
	case '^':
		return pow(lvalue, rvalue);
	default:
		throw("Invalid input!");
	}
}

const int evaluateRpn(const std::string input)
{
	std::stack<int> values;
	int lvalue{}, rvalue{}, result{};
	for (char symbol : input)
	{
		if (isDigit(symbol))
		{
			values.push(symbol - '0');
			continue;
		}

		rvalue = values.top();
		values.pop();
		lvalue = values.top();
		values.pop();
		result = calculate(lvalue, rvalue, symbol);
		values.push(result);
	}
	return values.top();
}

int main()
{
	std::string input = "(2^3+4*(7-2))*2^2^3";
	std::string output = polishNotation(input);
	std::cout << "Input: " << input << std::endl;
	std::cout << "Polish Notation: " << output << std::endl;
	std::cout << "Evaluation of PN: " << evaluateRpn(output) << std::endl;
	return 0;
}