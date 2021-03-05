/*
 * philosopher.cpp:
 *
 * Implementation of a dining philosopher class
 *
 *  Created on: 31 Jan 2020
 *      Author: Timothy Spain
 */

#include "philosopher.hpp"

#include <thread>
#include <sstream>
#include <iostream>

// Construct a philosopher from a name and two chopstick pointers
Philosopher::Philosopher(std::string name, Chopstick *left, Chopstick *right)
: name (name), left (left), right (right), have_l (false), have_r (false),
  eat_time (std::chrono::milliseconds(20)),
  think_time (std::chrono::milliseconds(30)),
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

void Philosopher::put_down_left(){
  if (have_l){
    left->set_down();
    have_l = false;
  }
}

void Philosopher::put_down_right(){
  if (have_r){
    right->set_down();
    have_r = false;
  }
}


// Getters for the boolean as to whether the instances holds each
// chopstick
bool Philosopher::have_left( ) {
	return have_l;
}

bool Philosopher::have_right( ) {
	return have_r;
}

// Eat! Tries to get both chopsticks, sleeps the thread while eating,
// and then puts down both chopsticks.
bool Philosopher::eat( ) {
	/* HANDS ON 3: Use the resource identifier from the Chopstick
	 * class to pick up in a fixed order. */
	if ( (!have_l && !get_left( )) || (!have_r && !get_right( )) ) {
		++hunger;
		return false;
	}

  std::this_thread::sleep_for(eat_time);
	hunger = 0;

  put_down_left();
  put_down_right();

	return true;
}

// Think! Keep chopsticks in hand while doing so
void Philosopher::think( ) {
	/* HANDS ON 2: Implement the try and wait algorithm by getting
	 * the philosophers to put down their chopsticks before thinking.
	 */
	std::this_thread::sleep_for(think_time);
	++hunger;
}

// Eat, think and be merry. Executes until the stop bool stops
// execution. Pauses execution when the pause boolean is set, and
// then increments the waiting counter to notify the pausing thread
void Philosopher::sympose(bool &stop, std::atomic<bool> &pause, std::atomic<int> &waiting, std::mutex &eat_exclusion) {
	std::default_random_engine engine(time(0));
	while (!stop) {
		if (pause) {
			waiting++;
			// Loop, sleeping, until the pause state is cleared
			while(pause)
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}


		int hunger_chance = 1 << hunger;
		// Randomly choose between thinking and eating, determined by
		// hunger
		if (std::uniform_int_distribution<int>(0,hunger_chance)(engine) == 0) {
			think( );
		} else {
			eat_exclusion.lock();
			bool has_et = eat( );
			eat_exclusion.unlock();
		}
	}
}

std::string Philosopher::get_name( ) {
	return name;
}

int Philosopher::get_hunger( ) {
	return hunger;
}
