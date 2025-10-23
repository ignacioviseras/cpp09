#pragma once

#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

class RPN {
private:
	std::stack<int> _stack;
	bool isOperator(const std::string &token) const;
	int calculateOperator(const std::string &op, int a, int b) const;
	
public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	int evaluate(const std::string &expression);
};



// You must create a program with these constraints:
// • The program name is RPN.
// • Your program must take an inverted Polish mathematical expression as an argument.
// • The numbers used in this operation and passed as arguments will always be less
// than 10. The calculation itself but also the result do not take into account this rule.
// • Your program must process this expression and output the correct result on the
// standard output.
// • If an error occurs during the execution of the program an error message should be
// displayed on the standard error.
// • Your program must be able to handle operations with these tokens: "+ - / *".
// You must use at least one container in your code to validate this
// exercise.
// You don’t need to handle brackets or decimal numbers.
// Here is an example of standard usage:
// $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
// 42
// $> ./RPN "7 7 * 7 -"
// 42
// $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
// 0
// $> ./RPN "(1 + 1)"
// Error
// $>
// Warning: The container(s) you used in the previous exercise are
// forbidden here. The container(s) you used to validate this exercise
// will not be usable for the rest of this module.