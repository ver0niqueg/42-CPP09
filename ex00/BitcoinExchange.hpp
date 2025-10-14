/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:51:31 by vgalmich          #+#    #+#             */
/*   Updated: 2025/10/14 18:09:49 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <map> // conteneur STL

class BitcoinExchange
{
    private:
        std::map<std::string, float> _database;

        std::string trim(const std::string& str);
        bool isValidDate(const std::string& date);
        bool isValidNumber(const std::string &str, float& value);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &copy);
        BitcoinExchange& operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        bool loadDatabase(const std::string filename);
        float getPrice(const std::string& data) const;
        void processInput(const std::string& filename);
};

#endif