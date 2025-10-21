/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:12:23 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/21 13:50:57 by vgalmich         ###   ########.fr       */
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
        if (i != isdigit(str[i]))
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
        throw std::runtime_error("Error: wrong number of arguments");
    
    for (int i = 0; i < argc; i++)
    {
        std::string arg(argv[i]);
    
        if (!isValidNumber(arg))
            throw std::runtime_error("Error: invalid input");
        
        int nb = atoi(arg.c_str());
        _vectorData.push_back(nb);
        _dequeData.push_back(nb);
    }
}


