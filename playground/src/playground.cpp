#include <chrono>
#include <iostream>
#include <list>
#include <vld.h>

#include <ntl/Forward_List.h>

using namespace std;
using namespace ntl;
using namespace chrono;

int main()
{
	auto start = high_resolution_clock::now();

	Forward_List<int> list;

	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	list.push_front(5);

	Forward_List<int> second_list(list);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	printf("Time SLList = %lld  millisecond\n", duration.count());


	return 0;
}