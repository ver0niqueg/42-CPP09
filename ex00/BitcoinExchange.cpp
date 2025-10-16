/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:51:43 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/16 16:53:24 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {_database = copy._database;};

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        this->_database = other._database;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {};

std::string BitcoinExchange::trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    if (start == std::string::npos)
        return "";
    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < date.length(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            false;
    }
    
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year < 1000 || year > 9999)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1)
        return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (isLeapYear && month == 2)
        daysInMonth[1] = 29;
    
    if (day > daysInMonth[month - 1])
        return false;
    
    return true;
}

bool BitcoinExchange::isValidNumber(const std::string &str, float& value)
{
    char *endptr;

    value = strtof(str.c_str(), &endptr); // str to float
    if (endptr == str.c_str())
        return false;

    if (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')
        return false;
    
        if (value < 0.0f || value > 1000.0f)
            return false;
    
    return true;
}

bool BitcoinExchange::loadDatabase(const std::string filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file." << std::endl;    
        return false;
    }
    
    std::string line;
    std::getline(file, line); // skip first line
    while (std::getline(file, line))
    {
        size_t pos = line.find(',');
        if (pos = std::string::npos)
            continue;
        std::string date = trim(line.substr(0, pos));
        std::string valueStr = trim(line.substr(pos + 1));
        
        float value = static_cast<float>(atof(valueStr.c_str())); // std::string to const char, to double, to float
        _database[date] = value;
    }
    file.close();
    return true;
    
        
}