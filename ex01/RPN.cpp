/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:29:47 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/20 17:56:43 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &copy) : _stack(copy._stack) {}

RPN& RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

RPN::~RPN() {}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::operate(int a, int b, char op) const
{
	switch (op)
	{
		case '+':
		   return (a + b);
		case '-':
			return (a - b);
		case '*':
			return (a * b);
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: division by zero");
			return (a / b);
		default:
			throw std::runtime_error("Error: invalid operator");
	}
}
		 
int RPN::processRPN(const std::string& expression)
{
	if (expression.empty())
		throw std::runtime_error("Error: empty expression");
	
	std::istringstream iss(expression); // flux d'entree qui lit depuis une chaine de caracteres
	std::string token; // va contenir chaque mot ou symbole extrait de la chaine

	while (iss >> token)
	{
		// si c'est un chiffre on l'empile
		if (token.length() == 1 && isdigit(token[0]))
			_stack.push(token[0] - '0');
		// si c'est un operateur
		else if (token.length() == 1 && isOperator(token[0]))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error: insufficient operands");
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			
			int result = operate(a, b, token[0]);
			_stack.push(result);
		}
		else
			throw std::runtime_error("Error: invalid token");
	}
	
	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid expression");

	int result = _stack.top();
	_stack.pop();
	return result;
}



