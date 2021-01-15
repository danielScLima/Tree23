cmake_minimum_required(VERSION 3.5.1)
project(Program VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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