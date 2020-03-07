#include<doctest/doctest.h>

#include <ntl/Min_Binary_Heap.h>

using namespace ntl;

TEST_CASE("[Binary Heap] insert function")
{
	Min_Binary_Heap<int> heap;

	heap.insert(40);
	heap.insert(20);
	heap.insert(10);
	heap.insert(8);
	heap.insert(15);
	heap.insert(50);

	CHECK(heap.size() == 6);

	auto min = heap.getMinimum();
	CHECK(min == 8);
	CHECK(heap.size() == 5);

	min = heap.getMinimum();
	CHECK(min == 10);
	CHECK(heap.size() == 4);


}