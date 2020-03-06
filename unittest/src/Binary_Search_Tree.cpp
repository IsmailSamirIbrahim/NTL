#include<doctest/doctest.h>

#include <ntl/Binary_Search_Tree.h>

using namespace ntl;

TEST_CASE("[BST] Insert")
{
	BST<int> tree;

	tree.insert(30);
	tree.insert(23);
	tree.insert(11);
	tree.insert(25);
	tree.insert(35);
	tree.insert(31);
	tree.insert(42);

	CHECK(tree.size() == 7);
	CHECK(tree.hasError() == false);
}


TEST_CASE("[BST] erase")
{
	BST<int> tree;

	tree.insert(30);
	tree.insert(23);
	tree.insert(11);
	tree.insert(25);
	tree.insert(35);
	tree.insert(31);
	tree.insert(42);

	tree.erase(30);

	CHECK(tree.size() == 6);
	CHECK(tree.find(30) == false);
}

TEST_CASE("[BST] clear")
{
	BST<int> tree;

	tree.insert(30);
	tree.insert(23);
	tree.insert(11);
	tree.insert(25);
	tree.insert(35);
	tree.insert(31);
	tree.insert(42);

	tree.clear();

	CHECK(tree.size() == 0);
	CHECK(tree.find(30) == false);
	CHECK(tree.empty() == true);
}

TEST_CASE("[BST] find")
{
	BST<int> tree;

	tree.insert(30);
	tree.insert(23);
	tree.insert(11);
	tree.insert(25);
	tree.insert(35);
	tree.insert(31);
	tree.insert(42);

	CHECK(tree.find(30) == true);
	CHECK(tree.find(23) == true);
	CHECK(tree.find(11) == true);
	CHECK(tree.find(25) == true);
	CHECK(tree.find(35) == true);
	CHECK(tree.find(31) == true);
	CHECK(tree.find(42) == true);
}

