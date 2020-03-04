/*
 * table.cpp
 *
 *	Definition of the table at which our philosophers are eating.
 *	Constructs the objects and sets of the thread which simulate the
 *	philosophers.
 *
 *  Created on: 4 Feb 2020
 *      Author: Tim Spain
 */

#include "table.hpp"

#include <random>
#include <thread>
#include <atomic>
#include <vector>
#include <list>
#include <iostream>
#include "../src_hierarchy/visualise.hpp"

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
}

void Table::sympose( ) {
	// Set up the stop boolean
	bool stop = false;
	// Set up the pause boolean and the atomic int counter of waiting philosophers
	std::atomic<bool> pause;
	pause = false;
	std::atomic<int> waiting;
	waiting = 0;
	// Create the philosopher threads
	for (int i = 0; i < philosophers.size(); i++) {
		threads[i] = move(std::thread(&Philosopher::sympose, std::ref(philosophers[i]), std::ref(stop), std::ref(pause), std::ref(waiting)));
	}
	// Create the timer thread, which halts execution after the specified number of milliseconds (3000)
	std::thread kill_thread(kill_timer, 3000, std::ref(stop));
	// Create the visualisation thread, which will occasionally pause execution to get the philosophers state
	std::thread visual_thread(visualise, std::ref(philosophers), std::ref(pause), std::ref(waiting), std::ref(stop));
	// Join the threads
	for (auto iter = threads.begin(); iter != threads.end(); iter++) {
		iter->join( );
	}
	kill_thread.join( );
	visual_thread.join();

}

// A function to stop the program after a given number of milliseconds
void kill_timer(int millis, bool &stop) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
	stop = true;
}
