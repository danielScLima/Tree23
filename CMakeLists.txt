cmake_minimum_required(VERSION 3.12)
project(Program VERSION 1.0.0)

include_directories(subprojects/LibToTree23/submodules/BTree/)

add_library(
	libtree23
	subprojects/LibToTree23/submodules/BTree/nodeOfBTree.h
	subprojects/LibToTree23/submodules/BTree/nodeOfBTree.cpp
	subprojects/LibToTree23/submodules/BTree/btree.h
	subprojects/LibToTree23/submodules/BTree/btree.cpp
	tree23.h
	tree23.cpp
)

add_executable(program program.cpp)

target_link_libraries(program PRIVATE libtree23)