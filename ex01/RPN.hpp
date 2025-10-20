/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:27:08 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/20 17:56:49 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

class RPN
{
	private:
		std::stack<int> _stack;

		bool isOperator(char c) const;
		int operate(int a, int b, char op) const;

	public:
		RPN();
		RPN(const RPN &copy);
		RPN& operator=(const RPN &other);
		~RPN();

		int processRPN(const std::string& expression);
};

#endif