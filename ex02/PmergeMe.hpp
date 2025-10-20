/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:28:08 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/20 22:28:08 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <sys/time.h>
#include <climits>
#include <iomanip>

class PmergeMe
{
	private:
		std::vector<int> _vectorData;
		std::deque<int> _dequeData;

		// parsing
		bool isValidNumber(const std::string& str);
		void parseInput(int argc, char** argv);

		template <typename Container>
		void fordJonhson(Container& arr);

		template <typename Container>
		void insertion(Container& arr, int left, int right);

		template <typename Container>
		void merge(Container& arr, int left, int mid, int right);

		template <typename Container>
		void printSequence(const std::string& prefix, const Container& data, size_t maxDisplay);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &other);
		~PmergeMe();

		void run(int argc, char** argv);
};


#endif