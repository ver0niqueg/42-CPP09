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
#include <algorithm>
#include <set>

class PmergeMe
{
	private:
		std::vector<int> _vectorData;
		std::deque<int> _dequeData;

		bool isValidNumber(const std::string& str);
		void parseInput(int argc, char** argv);

		std::vector<size_t> generateJacobsthalSequence(size_t n);

		// vector
		size_t binarySearchVector(const std::vector<int>& arr, int value, size_t end);
		std::vector<int> mergePairsVector(std::vector<std::pair<int, int> >& pairs);
		void insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pend);
		void fordJohnsonVector(std::vector<int>& arr);
	
		// deque
		size_t binarySearchDeque(const std::deque<int>& arr, int value, size_t end);
		std::deque<int> mergePairsDeque(std::deque<std::pair<int, int> >& pairs);
		void insertPendingDeque(std::deque<int>& mainChain, const std::deque<int>& pend);
		void fordJohnsonDeque(std::deque<int>& arr);
	
		template <typename Container>
		void printSequence(const std::string& prefix, const Container&);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &other);
		~PmergeMe();

		void execute(int argc, char** argv);
};

#endif