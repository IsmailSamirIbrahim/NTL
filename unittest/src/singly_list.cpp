#include <doctest/doctest.h>

//#include <vld.h>

#include <ntl/Singly_List.h>

using namespace std;
using namespace ntl;


TEST_CASE("[singly_list]: push_front")
{
	Single_List<int> list{};

	list.push_front(4);
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);

	CHECK(list.size() == 4);
	CHECK(list.front() == 1);
	CHECK(list.empty() == false);
}

TEST_CASE("[singly_list]: insert")
{
	Single_List<int> list{};

	list.insert(0, 4);
	list.insert(0, 3);
	list.insert(0, 2);
	list.insert(0, 1);

	CHECK(list.size() == 4);
	CHECK(list.front() == 1);
	CHECK(list.empty() == false);
}

TEST_CASE("[singly_list]: assign")
{
	Single_List<int> list{};

	list.assign({ 1, 2, 3, 4, 5 });

	CHECK(list.size() == 5);
	CHECK(list.front() == 5);
	CHECK(list.empty() == false);

	list.clear();
	CHECK(list.empty() == true);

	list.assign(4, 5);
	CHECK(list.size() == 4);
	CHECK(list.front() == 5);
}

TEST_CASE("[singly_list]: erase")
{
	Single_List<int> list{};

	list.assign({ 5, 4, 3, 2, 1 });

	CHECK(list.size() == 5);

	list.erase(0);

	CHECK(list.size() == 4);
	CHECK(list.front() == 2);
}