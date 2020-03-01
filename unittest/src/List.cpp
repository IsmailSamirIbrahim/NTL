#include <doctest/doctest.h>

//#include <vld.h>

#include <ntl/List.h>

using namespace std;
using namespace ntl;


TEST_CASE("[list]: push_front and push_back")
{
	List<int> list{};

	list.push_front(2);
	list.push_front(1);
	list.push_back(3);
	list.push_back(4);

	CHECK(list.size() == 4);
	CHECK(list.front() == 1);
	CHECK(list.back() == 4);
	CHECK(list.empty() == false);
}

TEST_CASE("[list]: assign")
{
	List<int> list{};

	list.assign({ 1, 2, 3, 4, 5 });

	CHECK(list.size() == 5);
	CHECK(list.front() == 1);
	CHECK(list.empty() == false);

	list.clear();
	CHECK(list.empty() == true);

	list.assign(4, 5);
	CHECK(list.size() == 4);
	CHECK(list.front() == 5);
}

TEST_CASE("[list]: erase")
{
	List<int> list{};

	list.assign({ 5, 4, 3, 2, 1 });

	CHECK(list.size() == 5);

	list.erase(0);

	CHECK(list.size() == 4);
	CHECK(list.front() == 4);
}