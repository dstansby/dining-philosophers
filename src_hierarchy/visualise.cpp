/*
 * visualise.cpp
 *
 *  Created on: 27 Feb 2020
 *      Author: tim
 */

#include "../src_hierarchy/visualise.hpp"

#include <vector>
#include <thread>
#include <iostream>

const int sleepy_time = 1;
const int repeat_time = 100;

void display_philosopher(std::ostream &os, Philosopher philosopher);


void visualise(std::vector<Philosopher> &philosophers, std::atomic<bool> &pause, std::atomic<int> &waiting, bool &stop) {

	while (!stop) {
		// Tell the philosophers to wait
		pause = true;
		// sleep until they have all reported as waiting
		while (waiting < philosophers.size()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepy_time));
		}

		for (auto iter = philosophers.begin();
				iter != philosophers.end();
				iter++) {
			display_philosopher(std::cout, *iter);
		}
		std::cout << std::endl << "-----------------------------" << std::endl << std::endl;
		waiting = 0;
		pause = false;

		std::this_thread::sleep_for(std::chrono::milliseconds(repeat_time));
	}
}

void display_philosopher(std::ostream &os, Philosopher philosopher) {
	os << "    "; // left margin
	os << (philosopher.have_left( ) ? "|" : " ");
	os << '\xe2' << '\x98' << '\xba'; // Smiling happy face
	os << (philosopher.have_right( ) ? "|" : " ");
	os << "    " << philosopher.get_name( ) << "(" << philosopher.get_hunger( ) << ")";
	os << std::endl;

}

