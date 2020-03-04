/*
 * philosophers.cpp
 *
 * Main function for the dining philosophers
 *
 *  Created on: 31 Jan 2020
 *      Author: Tim Spain
 */

#include <list>
#include <string>
#include "../src_hierarchy/table.hpp"

int main( ) {
	// Five philosophers from the Chinese Philosophy pages on Wikipedia
	std::list<std::string> names {"Kong Fuzi", "Duke Wen", "Shang Yang", "Mo Di", "Zou Yan"};

	Table table(names);

	table.sympose( );
}
