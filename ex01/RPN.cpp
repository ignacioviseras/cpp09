#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}

RPN::RPN(const RPN &other) {
	*this = other;
}

RPN &RPN::operator=(const RPN &other) {
	(void)other;
	return *this;
}

bool RPN::isOperator(const std::string &token) const {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::calculateOperator(const std::string &op, int a, int b) const{
	if (op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if (op == "*")
		return a * b;
	if (op == "/") {
		if (b==0)
			throw std::runtime_error("u cant divide by 0");
		return a/ b;
	 }
	throw std::runtime_error("invalid operator use + - * /");
}

int RPN::evaluate(const std::string &expression) {
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token) {
		if (isdigit(token[0]) && token.size() == 1)
			_stack.push(token[0] - '0');
		else if (isOperator(token)) {
			if (_stack.size() < 2)
				throw std::runtime_error("not enough operands");
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			_stack.push(calculateOperator(token, a, b));
		} else
			throw std::runtime_error("invalid");
	}
	if (_stack.size() != 1)
		throw std::runtime_error("invalid expression");
	return _stack.top();
	
}