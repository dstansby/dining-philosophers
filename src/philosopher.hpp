/*
 * philosopher.hpp
 *
 * Definition of the philosopher class.
 *
 *  Created on: 31 Jan 2020
 *      Author: Tim Spain
 */

#ifndef PHILOSOPHERS_PHILOSOPHER_HPP_
#define PHILOSOPHERS_PHILOSOPHER_HPP_

#include <string>
#include <chrono>
#include <random>
#include <atomic>

#include "chopstick.hpp"

class Philosopher {
	// Time spent eating or thinking, so that the program state
	// evolves ate a reasonable rate.
	const std::chrono::milliseconds eat_time;
	const std::chrono::milliseconds think_time;
private:
	std::string name; // The philosopher's name
	Chopstick *left, *right; // Pointers to the two chopsticks
							 // available
	bool have_l, have_r; // Booleans noting whether the philosopher
						 // holds the chopsticks
	int hunger; // How hungry is the philosopher? Controls the
				// relative probability of thinking or eating

public:
	Philosopher(std::string, Chopstick*, Chopstick*);

	// Try to get the two chopsticks, returning whether it was
	// successful.
	bool get_left( );
	bool get_right( );
	// Return whether the chopsticks are currently held
	bool have_left( );
	bool have_right( );

	// Execute the eat function, reducing hunger and returning true
	// if successful
	bool eat( );

	// Execute the think function, increasing hunger
	void think( );

	// Eat and think, stopping once stop is true, pausing when pause
	// is true and then incrementing the waiting counter
	void sympose(bool &stop, std::atomic<bool> &pause, std::atomic<int> &waiting);

	// Get the defined name
	std::string get_name( );
	// Get the current hunger value (number of thoughts without eating)
	int get_hunger( );
};


#endif /* PHILOSOPHERS_PHILOSOPHER_HPP_ */
