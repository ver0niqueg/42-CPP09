/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:29:47 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/17 19:09:39 by vgalmich         ###   ########.fr       */
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

bool RPN::isOperand(char c) const
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
        if (token.length() == 1 && isdigit(token[0]))
            _stack.push(token[0] - '0');
    }
}



