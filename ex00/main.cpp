#include "BitcoinExchange.hpp"

int main(int argc, char** argv) {
	
	if (argc != 2) {
		std::cerr << "Error: the program only have 2 params" << std::endl;
		return 1;
	}
	try {
		BitcoinExchange btc;
		btc.accessDB("./data.csv");
		btc.loadData(argv[1]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
