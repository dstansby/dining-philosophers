/*
 * table.hpp
 *
 * Declaration of the table at which our philosophers are eating
 *
 *  Created on: 31 Jan 2020
 *      Author: Tim Spain
 */

#ifndef PHILOSOPHERS_TABLE_HPP_
#define PHILOSOPHERS_TABLE_HPP_

#include <thread>
#include <vector>
#include <list>
#include <string>

#include "../src_hierarchy/chopstick.hpp"
#include "../src_hierarchy/philosopher.hpp"


class Table {
private:
	std::vector<Philosopher> philosophers;
	std::list<Chopstick> chopsticks;

	std::vector<std::thread> threads;

public:
	// Construct from a list of philosopher names
	Table(std::list<std::string> names);

	// Run the philosopher threads
	void sympose( );
};



#endif /* PHILOSOPHERS_TABLE_HPP_ */
