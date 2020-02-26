/*
 * test_philospher.cpp
 *
 *  Created on: 12 Feb 2020
 *      Author: tim
 */

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include "../src/chopstick.hpp"
#include "../src/philosopher.hpp"

TEST_CASE("Can philosophers eat?", "[Tests, philosopher]") {
	Chopstick left, right;
	Philosopher plato("Plato", &left, &right);

	REQUIRE(plato.eat());

	// Check Plato has relinquished his chopsticks
	REQUIRE(left.try_pick_up());
	left.set_down();
	REQUIRE(right.try_pick_up());
	right.set_down();


}
