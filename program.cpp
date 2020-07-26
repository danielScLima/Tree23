// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "tree23.h"

bool checkVectorOfEntriesInNode(NodeOfBTree* node, std::vector<int> vec)
{
	if (node->getVectorOfEntries().size() != vec.size())
		return false;
	
	for (int index = 0; index < vec.size(); ++index)
	{
		if (node->getVectorOfEntries().at(index) != vec.at(index))
			return false;
	}
	
	return true;
}

bool checkCountOfChilds(NodeOfBTree* node, int count)
{
	return node->getVectorOfPointers().size() == count;
}

TEST_CASE( "Testing the insert call in the tree23", "[single-file]" )
{
	Tree23 b;
	b.insert(50);
	
	NodeOfBTree* root = b.getRoot();
	
	REQUIRE( root != nullptr);
	REQUIRE( checkVectorOfEntriesInNode(root, {50}));
	
	b.insert(40);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {40,50}));
	
	b.insert(60);
	root = b.getRoot();
	
	REQUIRE( checkVectorOfEntriesInNode(root, {50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {60}));
	
	b.insert(70);
	root = b.getRoot();
	
	REQUIRE( checkVectorOfEntriesInNode(root, {50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {60,70}));
	
	b.insert(80);
	root = b.getRoot();
	
	REQUIRE( checkVectorOfEntriesInNode(root, {50,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {80}));
	
	b.insert(90);
	
	root = b.getRoot();
	
	REQUIRE( checkVectorOfEntriesInNode(root, {50,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {80,90}));
	
	b.insert(45);
	
	root = b.getRoot();
	
	REQUIRE( checkVectorOfEntriesInNode(root, {50,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,45}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {80,90}));
	
	b.insert(55);
	
	root = b.getRoot();
	
	REQUIRE( checkVectorOfEntriesInNode(root, {50,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,45}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {55,60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {80,90}));
	
	b.insert(85);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {70}));
	
	NodeOfBTree* leftChild = root->pointerByIndex(0);
	NodeOfBTree* rightChild = root->pointerByIndex(1);

	REQUIRE( checkVectorOfEntriesInNode(leftChild, {50}));	
	REQUIRE( checkVectorOfEntriesInNode(rightChild, {85}));
	
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(0), {40,45}));
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(1), {55,60}));
	
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(0), {80}));
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(1), {90}));
}

TEST_CASE( "Testing the remove call in the tree23", "[single-file]" )
{
	Tree23 b;
	
	b.insert(50);
	b.insert(40);
	b.insert(60);
	b.insert(70);
	b.insert(80);
	b.insert(90);
	b.insert(45);
	b.insert(55);
	b.insert(85);
	
	
	NodeOfBTree* root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {70}));
	
	NodeOfBTree* leftChild = root->pointerByIndex(0);
	NodeOfBTree* rightChild = root->pointerByIndex(1);

	REQUIRE( checkVectorOfEntriesInNode(leftChild, {50}));	
	REQUIRE( checkVectorOfEntriesInNode(rightChild, {85}));
	
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(0), {40,45}));
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(1), {55,60}));
	
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(0), {80}));
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(1), {90}));
	
	//This is the initial state
	
	//1 st remove
	b.remove(40);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {70}));
	
	leftChild = root->pointerByIndex(0);
	rightChild = root->pointerByIndex(1);

	REQUIRE( checkVectorOfEntriesInNode(leftChild, {50}));	
	REQUIRE( checkVectorOfEntriesInNode(rightChild, {85}));
	
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(0), {45}));
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(1), {55,60}));
	
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(0), {80}));
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(1), {90}));
	
	//2 nd remove
	b.remove(55); //aqui
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {70}));
	
	leftChild = root->pointerByIndex(0);
	rightChild = root->pointerByIndex(1);

	REQUIRE( checkVectorOfEntriesInNode(leftChild, {50}));	
	REQUIRE( checkVectorOfEntriesInNode(rightChild, {85}));
	
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(0), {45}));
	REQUIRE( checkVectorOfEntriesInNode(leftChild->pointerByIndex(1), {60}));
	
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(0), {80}));
	REQUIRE( checkVectorOfEntriesInNode(rightChild->pointerByIndex(1), {90}));
	
	b.remove(60);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {70,85}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {45,50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {80}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {90}));
	
	b.remove(80);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {50,85}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {45}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {90}));
	
	b.remove(45);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {85}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {50,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90}));
	
	b.remove(70);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {85}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90}));
	
	b.remove(90);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {50, 85}));
	
	b.remove(50);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {85}));
	
	b.remove(85);
	
	root = b.getRoot();

	REQUIRE( checkVectorOfEntriesInNode(root, {}));
}

TEST_CASE( "Testing the search call in the tree23", "[single-file]" )
{
	Tree23 b;
	
	std::vector<int> toInsert = 
	{50,40,60,70,80,90,45,55,85,75,65,35,30,20,21,22,23,25};
	
	for (auto number: toInsert)
		b.insert(number);
	
	for (auto number: toInsert)
		REQUIRE(b.search(number) != nullptr);
}

TEST_CASE( "Testing the search call in the tree23, second way", "[single-file]" )
{
	Tree23 b;
	
	std::vector<int> toInsert = 
	{50,40,60,70,80,90,45,55,85,75,65,35,30,20,21,22,23,25};
	
	for (auto number: toInsert)
		b.insert(number);

	std::vector<int> toRemove = 
	{90,85,21,60};
	
	for (auto number: toRemove)
		b.remove(number);
	
	for (auto number: toRemove)
		REQUIRE(b.search(number) == nullptr);
}

TEST_CASE( "Testing the insert call of duplicated entries in the tree23", "[single-file]" )
{
	Tree23 b;
	
	REQUIRE(b.insert(50));
	REQUIRE(b.insert(40));
	REQUIRE(b.insert(60));
	REQUIRE(b.insert(70));
	
	REQUIRE(!b.insert(50));
	REQUIRE(!b.insert(40));
	REQUIRE(!b.insert(60));
	REQUIRE(!b.insert(70));
}