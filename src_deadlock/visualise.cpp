/*
 * visualise.cpp
 *
 *	Implement the visualisation of the dining philosophers.
 *
 *  Created on: 27 Feb 2020
 *      Author: tim
 */

#include "visualise.hpp"

#include <vector>
#include <thread>
#include <iostream>

const int sleepy_time = 1;
const int repeat_time = 100;

void display_philosopher(std::ostream &os, Philosopher philosopher);

// Loop until told to stop (stop bool), waiting until all philosophers are paused and then displaying their current state.
void visualise(std::vector<Philosopher> &philosophers, std::atomic<bool> &pause, std::atomic<int> &waiting, bool &stop) {

	while (!stop) {
		// Tell the philosophers to wait, resetting the waiting thread count
		waiting = 0;
		pause = true;
		// sleep until they have all reported as waiting
		while (waiting < philosophers.size()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepy_time));
		}

		// Iterate over the provided philosophers and display their state
		for (auto iter = philosophers.begin();
				iter != philosophers.end();
				iter++) {
			display_philosopher(std::cout, *iter);
		}
		std::cout << std::endl << "-----------------------------" << std::endl << std::endl;
		// Unset the pause flag
		pause = false;

		// Sleep until the next display is scheduled
		std::this_thread::sleep_for(std::chrono::milliseconds(repeat_time));
	}
}

// Print the philosopher's face, their held chopsticks, name and hunger level
void display_philosopher(std::ostream &os, Philosopher philosopher) {
	os << "    "; // left margin
	os << (philosopher.have_left( ) ? "|" : " ");
	os << '\xe2' << '\x98' << '\xba'; // Smiling happy face
	os << (philosopher.have_right( ) ? "|" : " ");
	os << "    " << philosopher.get_name( ) << "(" << philosopher.get_hunger( ) << ")";
	os << std::endl;

}

