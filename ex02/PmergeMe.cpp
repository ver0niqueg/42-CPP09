/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:12:23 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/24 15:31:35 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy) : _vectorData(copy._vectorData), _dequeData(copy._dequeData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vectorData = other._vectorData;
		_dequeData = other._dequeData;
	}
	return (*this);
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isValidNumber(const std::string& str)
{
	if (str.empty())
		return false;
		
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}

	std::stringstream ss(str);
	long nb;
	ss >> nb;
	if (nb < 0 || nb > INT_MAX)
		return false;

	return true;
}

void PmergeMe::parseInput(int argc, char** argv)
{
    if (argc < 2)
        throw std::runtime_error("Error: no input sequence provided");
    
    std::set<int> seen;
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (!isValidNumber(arg))
            throw std::runtime_error("Error: invalid input");
        
        int nb = atoi(arg.c_str());
        if (seen.count(nb))
            throw std::runtime_error("Error: duplicate input");
        seen.insert(nb);

        _vectorData.push_back(nb);
        _dequeData.push_back(nb);
    }
    
    if (_vectorData.empty())
        throw std::runtime_error("Error: empty sequence");
}

/* Generates the Jacobsthal sequence : 0, 1, 1, 3, 5, 11, 21, 43, ...
in order to determine the insertion order for pending elements.
It minimizes comparisons during merge-insertion sorting */
std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t n)
{
	std::vector<size_t> jacobsthal;
	
	if (n == 0)
		return jacobsthal;
	
	jacobsthal.push_back(0);
	if (n == 1)
		return jacobsthal;

	jacobsthal.push_back(1);
	
	size_t j_prev2 = 0;
	size_t j_prev1 = 1;
	
	while (true)
	{
		size_t j_next = j_prev1 + 2 * j_prev2;
		if (j_next >= n)
			break;
		jacobsthal.push_back(j_next);
		j_prev2 = j_prev1;
		j_prev1 = j_next;
	}
	
	return jacobsthal;
}

//=============== Vector Implementation ===============//

/* Performs a binary search on the range [0, end) of 'arr' to find
the correct insertion position for 'value'. */
size_t PmergeMe::binarySearchVector(const std::vector<int>& arr, int value, size_t end)
{
	size_t left = 0;
	size_t right = end;
	
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (arr[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	return left;
}

/* Recursively merges pairs to produce a sorted vector of the larger elements.
If there is only one pair, returns the larger value of that pair.
Uses a merge sort process to combine the left and right halves. */
std::vector<int> PmergeMe::mergePairsVector(std::vector<std::pair<int, int> >& pairs)
{
	if (pairs.empty())
		return std::vector<int>();
	
	if (pairs.size() == 1)
	{
		std::vector<int> result;
		result.push_back(pairs[0].second);
		return result;
	}
	
	size_t mid = pairs.size() / 2;
	std::vector<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
	std::vector<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());

	std::vector<int> leftSorted = mergePairsVector(left);
	std::vector<int> rightSorted = mergePairsVector(right);

	std::vector<int> result;
	size_t i = 0, j = 0;

	// fusion
	while (i < leftSorted.size() && j < rightSorted.size())
	{
		if (leftSorted[i] <= rightSorted[j])
			result.push_back(leftSorted[i++]);
		else
			result.push_back(rightSorted[j++]);
	}
	
	while (i < leftSorted.size())
		result.push_back(leftSorted[i++]);
	while (j < rightSorted.size())
		result.push_back(rightSorted[j++]);
	
	return result;
}

/* Inserts elements from 'pend' into 'mainChain' following the Jacobsthal insertion order.
Uses binary search to find the correct position in 'mainChain' for each element. */
void PmergeMe::insertPendingVector(std::vector<int>& mainChain, const std::vector<int>& pend)
{
	if (pend.empty())
		return ;
	
	std::vector<size_t> jacobsthal = generateJacobsthalSequence(pend.size() + 1);
	
	std::vector<size_t> insertionOrder;
	size_t lastPos = 0;
	
	for (size_t i = 2; i < jacobsthal.size(); i++)
	{
		size_t currentJacob = jacobsthal[i];

		if (currentJacob > pend.size())
			currentJacob = pend.size();
		
		for (size_t j = currentJacob; j > lastPos && j > 0; j--)
			insertionOrder.push_back(j - 1);
	
		lastPos = currentJacob;

		if (lastPos >= pend.size())
			break;
	}

	for (size_t i = lastPos; i < pend.size(); i++)
		insertionOrder.push_back(i);
	
	for (size_t i = 0; i < insertionOrder.size(); i++)
	{
		size_t idx = insertionOrder[i];
		if (idx < pend.size())
		{
			int value = pend[idx];
			size_t pos = binarySearchVector(mainChain, value, mainChain.size());
			mainChain.insert(mainChain.begin() + pos, value);
		}
	}
}

/* Implements the Ford–Johnson (Merge-Insertion) sorting algorithm on 'arr' */ 
void PmergeMe::fordJohnsonVector(std::vector<int>& arr)
{
	size_t n = arr.size();
	if (n <= 1)
		return ;
	
	std::vector<std::pair<int, int> > pairs;
	bool hasStraggler = (n % 2 != 0);
	int straggler = hasStraggler ? arr[n - 1] : 0;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		int a = arr[i];
		int b = arr[i + 1];
		if (a > b)
			pairs.push_back(std::make_pair(b, a));
		else
			pairs.push_back(std::make_pair(a, b));
	}

	std::vector<int> mainChain = mergePairsVector(pairs);
	
	std::vector<int> pend;

	if (!pairs.empty())
	{
		for (size_t i = 0; i < pairs.size(); i++)
		{
			pend.push_back(pairs[i].first);
		}
	}
	
	if (!pend.empty())
	{
		mainChain.insert(mainChain.begin(), pend[0]);
		pend.erase(pend.begin());
	}

	insertPendingVector(mainChain, pend);

	if (hasStraggler)
	{
		size_t pos = binarySearchVector(mainChain, straggler, mainChain.size());
		mainChain.insert(mainChain.begin() + pos, straggler);
	}
	arr = mainChain;
}

//=============== Deque Implementation ===============//

size_t PmergeMe::binarySearchDeque(const std::deque<int>& arr, int value, size_t end)
{
	size_t left = 0;
	size_t right = end;
	
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (arr[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	return left;
}

std::deque<int> PmergeMe::mergePairsDeque(std::deque<std::pair<int, int> >& pairs)
{
    if (pairs.empty())
        return std::deque<int>();

    if (pairs.size() == 1)
    {
        std::deque<int> result;
        result.push_back(pairs[0].second);
        return result;
    }
    
    size_t mid = pairs.size() / 2;
    std::deque<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
    std::deque<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());

    std::deque<int> leftSorted = mergePairsDeque(left);
    std::deque<int> rightSorted = mergePairsDeque(right);
    
    std::deque<int> result;
    size_t i = 0, j = 0;

    while (i < leftSorted.size() && j < rightSorted.size())
    {
        if (leftSorted[i] <= rightSorted[j]) 
            result.push_back(leftSorted[i++]);
        else
            result.push_back(rightSorted[j++]);
    }
    // ajouter les restes correctement
    while (i < leftSorted.size())
        result.push_back(leftSorted[i++]);
    while (j < rightSorted.size())
        result.push_back(rightSorted[j++]);

    return result;
}

void PmergeMe::insertPendingDeque(std::deque<int>& mainChain, const std::deque<int>& pend)
{
	if (pend.empty())
		return ;
	
	std::vector<size_t> jacobsthal = generateJacobsthalSequence(pend.size() + 1);
	
	std::vector<size_t> insertionOrder;
	size_t lastPos = 0;

	for (size_t i = 2; i < jacobsthal.size(); i++)
	{
		size_t currentJacob = jacobsthal[i];

		if (currentJacob > pend.size())
			currentJacob = pend.size();
		
		for (size_t j = currentJacob; j > lastPos && j > 0; j--)
			insertionOrder.push_back(j - 1);
		
		lastPos = currentJacob;
		if (lastPos >= pend.size())
			break;
	}
	
	for (size_t i = lastPos; i < pend.size(); i++)
		insertionOrder.push_back(i);
	
	for (size_t i = 0; i < insertionOrder.size(); i++)
	{
		size_t idx = insertionOrder[i];
		if (idx < pend.size())
		{
			int value = pend[idx];
			size_t pos = binarySearchDeque(mainChain, value, mainChain.size());
			mainChain.insert(mainChain.begin() + pos, value);       
		}
	}  
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr)
{
    size_t n = arr.size();
    if (n <= 1)
        return ;
    
    std::deque<std::pair<int, int> > pairs;
    bool hasStraggler = (n % 2 != 0);
    int straggler = hasStraggler ? arr[n - 1] : 0;
    
    for (size_t i = 0; i + 1 < n; i+= 2)
    {
        int a = arr[i];
        int b = arr[i + 1];
        if (a > b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    
    std::deque<int> mainChain = mergePairsDeque(pairs);
    
    std::deque<int> pend;

    if (!pairs.empty())
    {
        for (size_t i = 0; i < pairs.size(); i++)
        {
            pend.push_back(pairs[i].first);
        }
        if (!pend.empty())
        {
            mainChain.insert(mainChain.begin(), pend.front());
            pend.pop_front();
        }
    }

    insertPendingDeque(mainChain, pend);

    if (hasStraggler)
    {
        size_t pos = binarySearchDeque(mainChain, straggler, mainChain.size());
        mainChain.insert(mainChain.begin() + pos, straggler);
    }
    arr = mainChain;
}

template <typename Container>
void PmergeMe::printSequence(const std::string& prefix, const Container& data)
{
	std::cout << prefix;
	for (size_t i = 0; i < data.size(); i++)
	{
		std::cout << data[i];
		if (i < data.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::execute(int argc, char** argv)
{
	parseInput(argc, argv);

	printSequence("Before: ", _vectorData);

	struct timeval start, end;
	gettimeofday(&start, NULL);

	fordJohnsonVector(_vectorData);

	gettimeofday(&end, NULL);
	double vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0;
	vectorTime += (end.tv_usec - start.tv_usec);

	gettimeofday(&start, NULL);

	fordJohnsonDeque(_dequeData);

	gettimeofday(&end, NULL);
	double dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0;
	dequeTime += (end.tv_usec - start.tv_usec);

	printSequence("After: ", _vectorData);

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vectorData.size()
		<< " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _dequeData.size()
		<< " elements with std::quede : " << dequeTime << " us" << std::endl;
}

