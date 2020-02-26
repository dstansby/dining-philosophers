/*
 * philosopher.hpp
 *
 * Definition of the philosopher class
 *
 *  Created on: 31 Jan 2020
 *      Author: tim
 */

#ifndef PHILOSOPHERS_PHILOSOPHER_HPP_
#define PHILOSOPHERS_PHILOSOPHER_HPP_

#include <string>
#include <chrono>
#include <random>

#include "chopstick.hpp"

class Philosopher {
	const std::chrono::milliseconds eat_time;
	const std::chrono::milliseconds think_time;
	const static int hunger_threshold = 5;
private:
	std::string name;
	Chopstick *left, *right;
	bool have_l, have_r;
	int hunger;

public:
	Philosopher(std::string, Chopstick*, Chopstick*);

	bool get_left( );
	bool get_right( );
	bool have_left( );
	bool have_right( );

	bool eat( );

	void think( );

	void sympose(std::default_random_engine&, bool&);

	std::string get_name( );
};


#endif /* PHILOSOPHERS_PHILOSOPHER_HPP_ */
