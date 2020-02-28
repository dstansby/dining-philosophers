/*
 * table.cpp
 *
 *	Definition of the table at which our philosophers are eating
 *
 *  Created on: 4 Feb 2020
 *      Author: tim
 */

#include "../src_hierarchy/table.hpp"

#include <random>
#include <thread>
#include <atomic>
#include <vector>
#include <list>
#include <iostream>
#include "../src_hierarchy/visualise.hpp"

void randomize_philosophize(Philosopher &phil, int i, bool &stop, std::atomic<bool> &pause, std::atomic<int> &waiting);
void kill_timer(int millis, bool &stop);

Table::Table(std::list<std::string> names)
: chopsticks( ), philosophers( ), threads(names.size( ))
{
	int n_phil = names.size( );

	// Create all chopsticks
	for (int i = 0; i < n_phil; i++) {
		chopsticks.emplace_back(i);
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
	std::atomic<bool> pause;
	pause = false;
	std::atomic<int> waiting;
	waiting = 0;
	// Create the philosopher threads
	for (int i = 0; i < philosophers.size(); i++) {
		threads[i] = move(std::thread(randomize_philosophize, std::ref(philosophers[i]), i, std::ref(stop), std::ref(pause), std::ref(waiting)));
	}
	std::thread kill_thread(kill_timer, 3000, std::ref(stop));
	std::thread visual_thread(visualise, std::ref(philosophers), std::ref(pause), std::ref(waiting), std::ref(stop));
	// Join the threads
	for (auto iter = threads.begin(); iter != threads.end(); iter++) {
		iter->join( );
	}
	kill_thread.join( );
	visual_thread.join();

}

void randomize_philosophize(Philosopher &phil, int i, bool &stop, std::atomic<bool> &pause, std::atomic<int> &waiting) {
	std::default_random_engine engine(time(0)+i);
	phil.sympose(engine, stop, pause, waiting);
}

void kill_timer(int millis, bool &stop) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
	stop = true;
}
