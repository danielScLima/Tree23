cmake_minimum_required(VERSION 3.12)
project(Program VERSION 1.0.0)

add_library(
	libtree23
	nodeOfBTree.h
	nodeOfBTree.cpp
	btree.h
	btree.cpp
	tree23.h
	tree23.cpp
)

add_executable(program program.cpp)

target_link_libraries(program PRIVATE libtree23)