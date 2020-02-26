/*
 * philosophers.cpp
 *
 * Implementation of the philosopher class
 *
 *  Created on: 31 Jan 2020
 *      Author: tim
 */

#include "table.hpp"

#include <list>
#include <string>

int main( ) {
	// Five philosophers
	std::list<std::string> names {"Kong Fuzi", "Duke Wen", "Shang Yang", "Mo Di", "Zou Yan"};

	Table table(names);

	table.sympose( );
}
