/*
 * philosopher.cpp:
 *
 * Implementation of a dining philosopher
 *
 *  Created on: 31 Jan 2020
 *      Author: tim
 */

#include "philosopher.hpp"

#include <thread>
#include <sstream>
#include <iostream>

Philosopher::Philosopher(std::string name, Chopstick *left, Chopstick *right)
: name (name), left (left), right (right), have_l (false), have_r (false),
  eat_time (std::chrono::milliseconds(200)),
  think_time (std::chrono::milliseconds(300)),
  hunger (0)
{ }

// Try to get left (right) chopstick. Returns true on success.
bool Philosopher::get_left( ) {
	have_l = left->try_pick_up( );
	return have_l;
}

bool Philosopher::get_right( ) {
	have_r = right->try_pick_up( );
	return have_r;
}

// Getters for having chopsticks
bool Philosopher::have_left( ) {
	return have_l;
}

bool Philosopher::have_right( ) {
	return have_r;
}

// Eat! Tries to get both chopsticks, sleeps the thread while eating,
// and then puts down both chopsticks.
bool Philosopher::eat( ) {
	if ( (!have_l && !get_left( )) || (!have_r && !get_right( )) ) {
		++hunger;
		return false;
	}

	std::this_thread::sleep_for(eat_time);

	hunger = 0;

	left->set_down( );
	have_l = false;
	right->set_down( );
	have_r = false;

	return true;
}

// Think! Keep chopsticks in hand while doing so
void Philosopher::think( ) {
	++hunger;
}

void Philosopher::sympose(std::default_random_engine& engine, bool &stop) {
	int sleepo = std::uniform_int_distribution<int>(0,255)(engine);
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepo));
	while (!stop) {
		int hunger_chance = 1 << hunger;
		std::cout << name;
		if (std::uniform_int_distribution<int>(0,hunger_chance)(engine) == 0) {
			think( );
			std::cout << " has thought" << std::endl;
		} else {
			bool has_et = eat( );
			std::cout << (has_et ? " has eaten" : " couldn't eat") << std::endl;
		}
		const int hungry_limit = hunger_threshold;
		const int very_hungry_limit = 2 * hunger_threshold;
		std::stringstream ss;
		if (hunger > hungry_limit) {
			ss << name << " is " << ((hunger > very_hungry_limit) ? "very ": " ") << "hungry (" << hunger << ")."<< std::endl;
			std::cout << ss.str();
		}
	}
}

std::string Philosopher::get_name( ) {
	return name;
}
