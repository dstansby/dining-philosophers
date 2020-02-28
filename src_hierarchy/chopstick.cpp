/*
 * chopstick.cpp
 *
 *  Created on: 31 Jan 2020
 *      Author: tim
 */

#include "../src_hierarchy/chopstick.hpp"

Chopstick::Chopstick( )
: mutt() { }

bool Chopstick::try_pick_up( ) {
	return mutt.try_lock();
}

void Chopstick::set_down( ) {
	mutt.unlock( );
}

int Chopstick::get_resource_id( ) {
	return resource_id;
}
