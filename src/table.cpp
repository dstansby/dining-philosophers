/*
 * table.cpp
 *
 *	Definition of the table at which our philosophers are eating
 *
 *  Created on: 4 Feb 2020
 *      Author: tim
 */

#include "table.hpp"

#include <random>
#include <thread>
#include <vector>
#include <list>
#include <iostream>

void randomize_philosophize(Philosopher &phil, int i, bool &stop);
void kill_timer(int millis, bool &stop);

Table::Table(std::list<std::string> names)
: chopsticks( ), philosophers( ), threads(names.size( ))
{
	int n_phil = names.size( );

	// Create all chopsticks
	for (int i = 0; i < n_phil; i++) {
		chopsticks.emplace_back( );
	}

	// Create all philosophers, and assign their chopsticks, wrapping the right iterator if the end of the list is reached.
	int i = 0;
	auto left = chopsticks.begin();
	auto right = ++chopsticks.begin();
	for (auto iname = names.begin(); iname != names.end(); iname++) {
		philosophers.emplace_back(*iname, &(*left), &( (right != chopsticks.end()) ? *right : chopsticks.front()));
		++left;
		++right;
	}
	std::cout << "There are " << philosophers.size() << " philosophers." << std::endl;
}

void Table::sympose( ) {
	bool stop = false;
	// Create the philosopher threads
	for (int i = 0; i < philosophers.size(); i++) {
		threads[i] = move(std::thread(randomize_philosophize, std::ref(philosophers[i]), i, std::ref(stop)));
	}
	std::thread kill_thread(kill_timer, 1000, std::ref(stop));
	// Join the threads
	for (auto iter = threads.begin(); iter != threads.end(); iter++) {
		iter->join( );
	}
	kill_thread.join( );

}

void randomize_philosophize(Philosopher &phil, int i, bool &stop) {
	std::default_random_engine engine(time(0)+i);
	phil.sympose(engine, stop);
}

void kill_timer(int millis, bool &stop) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
	stop = true;
}
