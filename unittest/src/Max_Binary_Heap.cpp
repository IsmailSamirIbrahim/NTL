#include<doctest/doctest.h>

#include <ntl/Max_Binary_Heap.h>

using namespace ntl;

TEST_CASE("[Binary Heap] insert function")
{
	Max_Binary_Heap<int> heap;

	heap.insert(40);
	heap.insert(20);
	heap.insert(10);
	heap.insert(8);
	heap.insert(15);
	heap.insert(50);

	CHECK(heap.size() == 6);

	auto max = heap.getMaximum();
	CHECK(max == 50);
	CHECK(heap.size() == 5);

	max = heap.getMaximum();
	CHECK(max == 40);
	CHECK(heap.size() == 4);


}