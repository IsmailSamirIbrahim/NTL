#include <chrono>
#include <iostream>
#include <list>
//#include <vld.h>

#include <ntl/Singly_List.h>

using namespace std;
using namespace ntl;
using namespace chrono;

int main()
{
	auto start = high_resolution_clock::now();

	Single_List<int> list;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	printf("Time SLList = %lld  millisecond\n", duration.count());


	return 0;
}