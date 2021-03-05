/*
 * chopstick.cpp
 *
 *	Chopstick class implementation for the dining philosophers
 *	problem. A thin wrapper around a std::mutex.
 *
 *  Created on: 31 Jan 2020
 *      Author: Tim Spain
 */

#include "chopstick.hpp"

Chopstick::Chopstick(int rid)
: mutt(), resource_id(rid) { }

bool Chopstick::try_pick_up( ) {
	return mutt.try_lock();
}

void Chopstick::set_down( ) {
	mutt.unlock( );
}

int Chopstick::get_resource_id(){
	return resource_id;
}
