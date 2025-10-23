#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_database = other._database;
	return *this;
}

void BitcoinExchange::calculate(const std::string& date, float value) const {
	std::map<std::string, float>::const_iterator iter = _database.lower_bound(date);
	if (iter == _database.end())
		--iter;
	else if (iter->first != date && iter != _database.begin())
		--iter;
	float rate = iter->second;
	std::cout << date << " => " << value << " = " << rate * value << std::endl;
}

bool isValidDate(const std::string& date) {
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    for (size_t i = 0; i < yearStr.size(); i++)
        if (!isdigit(yearStr[i]))
			return false;
    for (size_t i = 0; i < monthStr.size(); i++)
        if (!isdigit(monthStr[i]))
			return false;
    for (size_t i = 0; i < dayStr.size(); i++)
        if (!isdigit(dayStr[i]))
			return false;

    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());

    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    return true;
}

bool isValidValue(const std::string& valueStr, float& value) {
    char* end;
    value = std::strtof(valueStr.c_str(), &end);

    if (*end != '\0')
        return false;
    if (value < 0)
        throw std::runtime_error("Error: not a positive number.");
    if (value > 1000)
        throw std::runtime_error("Error: too large a number.");

    return true;
}


void BitcoinExchange::accessDB(const std::string& fileN) {

	std::ifstream file(fileN.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("error: couldnt open the file");
	}
	std::string line;
	std::getline(file, line);//omited first line (header)
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string date, value;
		// 2010-10-01,0.06
		// in the get line we split the data using ","
		// 2010-10-01 date
		// 0.06 value 
		std::getline(ss, date, ',');
		std::getline(ss, value);
		_database[date] = std::strtof(value.c_str(), NULL);
	}
	
}

/*
	with this u skip the spaces and tabs in the first part and the end of a str
*/
void trimContent(std::string &str) {
	str.erase(0, str.find_first_not_of(" \t"));
	str.erase(str.find_last_not_of(" \t") + 1);
}

void BitcoinExchange::loadData(const std::string& fileN) {
	std::ifstream input(fileN.c_str());
	if (!input.is_open())
		throw std::runtime_error("Error: couldnt open");
	std::string file, line;
	std::getline(input, line);
	while (std::getline(input, line)) {
		if (line.empty())
			continue;
		std::string date, valueStr;
		std::stringstream ss(line);

		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) {
			std::cerr << "error bad input: " << line << std::endl;
			continue;
		}

        trimContent(date);
        trimContent(valueStr);
		if (!isValidDate(date)) {
            std::cerr << "Error: bad date " << date << std::endl;
            continue;
        }
		float value;
		try {
			if (!isValidValue(valueStr, value)) {
				std::cerr << "error bad value " << valueStr << std::endl;
				continue;
			}
			calculate(date, value);
		} catch(const std::exception& e) {
			std::cerr << e.what() <<  std::endl;
		}
		
	}
	
}