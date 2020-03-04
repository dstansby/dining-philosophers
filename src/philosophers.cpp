/*
 * philosophers.cpp
 *
 * Main function for the dining philosophers
 *
 *  Created on: 31 Jan 2020
 *      Author: Tim Spain
 */

#include "table.hpp"

#include <list>
#include <string>

int main( ) {
	// Five philosophers from the Chinese Philosophy pages on Wikipedia
	std::list<std::string> names {"Kong Fuzi", "Duke Wen", "Shang Yang", "Mo Di", "Zou Yan"};

	Table table(names);

	table.sympose( );
}
