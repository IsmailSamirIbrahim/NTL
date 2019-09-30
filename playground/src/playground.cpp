#include <chrono>
#include <iostream>
#include <list>
//#include <vld.h>

#include <ntl/single_list.h>

using namespace std;
using namespace ntl;
using namespace chrono;

int main()
{
	auto start = high_resolution_clock::now();

	SLList list = sllist_new<int>();
	for (int i = 0; i < 900000000; ++i)
		sllist_push_back(list, i);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	printf("Time SLList = %lld  millisecond\n", duration.count());


	start = high_resolution_clock::now();

	std::list<int> l;
	for (int i = 0; i < 900000000; ++i)
		l.push_back(i);

	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	printf("Time = %lld  millisecond\n", duration.count());


	sllist_free(list);

	return 0;
}