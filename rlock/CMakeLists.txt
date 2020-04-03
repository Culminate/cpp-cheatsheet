cmake_minimum_required(VERSION 3.7.2)

set(PROJECT1 rlock)
set(PROJECT2 norlock)

set(SOURCES
	main.cpp
	)

set(INCLUDES
	thread.hpp
	)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)

add_executable(${PROJECT1} ${SOURCES} ${INCLUDES})
target_link_libraries(${PROJECT1} Threads::Threads)
target_compile_definitions(${PROJECT1} PRIVATE REC=1)


add_executable(${PROJECT2} ${SOURCES} ${INCLUDES})
target_link_libraries(${PROJECT2} Threads::Threads)
target_compile_definitions(${PROJECT2} PRIVATE REC=0)