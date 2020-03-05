cmake_minimum_required(VERSION 3.0)

project(philosophers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( Threads )

add_executable(philosophers src/philosophers.cpp
	src/table.cpp
	src/philosopher.cpp
	src/chopstick.cpp
	src/visualise.cpp
)
target_link_libraries(philosophers ${CMAKE_THREAD_LIBS_INIT} )
