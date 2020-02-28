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

add_executable(philosophers_try_wait src/philosophers.cpp
	src/table.cpp
	src/philosopher_try_wait.cpp
	src/chopstick.cpp
	src/visualise.cpp
)
target_link_libraries(philosophers_try_wait ${CMAKE_THREAD_LIBS_INIT} )



enable_testing()

add_executable(test_philosopher test/test_philosopher.cpp
	src/philosopher.cpp
	src/chopstick.cpp)
add_test(test_philosopher_test test_philosopher)
