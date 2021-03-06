/*
 * chopstick.cpp
 *
 *	Chopstick class implementation for the dining philosophers
 *	problem. A wrapper around a std::mutex, with an additional
 *	resource id.
 *
 *  Created on: 31 Jan 2020
 *      Author: Tim Spain
 */

#include "../src_hierarchy/chopstick.hpp"

Chopstick::Chopstick(int rid)
: mutt(), resource_id(rid) { }

bool Chopstick::try_pick_up( ) {
	return mutt.try_lock();
}

void Chopstick::set_down( ) {
	mutt.unlock( );
}

int Chopstick::get_resource_id( ) {
	return resource_id;
}
