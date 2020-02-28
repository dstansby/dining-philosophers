/*
 * chopstick.hpp
 *
 *  Created on: 31 Jan 2020
 *      Author: tim
 */

#ifndef PHILOSOPHERS_CHOPSTICK_HPP_
#define PHILOSOPHERS_CHOPSTICK_HPP_

#include <mutex>

class Chopstick {
private:
	std::mutex mutt;
public:
	Chopstick();

	bool try_pick_up();
	void set_down();

};

#endif /* PHILOSOPHERS_CHOPSTICK_HPP_ */
