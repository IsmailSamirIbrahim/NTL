#include <doctest/doctest.h>

#include <chrono>
#include <iostream>
#include <sstream>
//#include <vld.h>

#include <ntl/single_list.h>

using namespace std;
using namespace ntl;
using namespace chrono;


TEST_CASE("single list")
{
	auto start = high_resolution_clock::now();

	SLList list = sllist_new<int>();
	for (int i = 0; i < 10; ++i)
		sllist_push_back(list, i);

	for (int i = 0; i < 5; ++i)
		sllist_pop_front(list);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	printf("Time = %lld  millisecond\n", duration.count());
	
	
	
	sllist_free(list);
}