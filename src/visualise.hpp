/*
 * visualise.hpp
 *
 *  Created on: 27 Feb 2020
 *      Author: tim
 */

#include "philosopher.hpp"

#include <vector>
#include <list>
#include <mutex>

#ifndef SRC_VISUALISE_HPP_
#define SRC_VISUALISE_HPP_

void visualise(std::vector<Philosopher> &philosophers, std::atomic<bool> &pause, std::atomic<int> &waiting, bool &stop);

#endif /* SRC_VISUALISE_HPP_ */
