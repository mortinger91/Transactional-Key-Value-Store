cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(LIBRARY_TARGET_NAME "TransactionalStore")
project(${LIBRARY_TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(
	store src/main.cpp
)

target_link_libraries(
	store
	PRIVATE
	${LIBRARY_TARGET_NAME}
)
