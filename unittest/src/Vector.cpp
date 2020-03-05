#include<doctest/doctest.h>

#include <ntl/Vector.h>
#include <memory>

using namespace ntl;

TEST_CASE("[Vector] vector construction")
{
	Vector<int> v1(5);
	Vector<int> v2(5, 10);
	Vector<int> v3 = { 1, 2, 3, 4 };
	Vector<int> v4 = v3;
	Vector<int> v5(v3);
	Vector<int> v;
	v = v3;
	Vector<int> vv;
	vv = std::move(v);
}

TEST_CASE("[Vector] vector access functions")
{
	Vector<int> v = { 1, 2, 3, 4, 5 };

	size_t front = v.front();
	CHECK(front == 1);

	size_t back = v.back();
	CHECK(back == 5);

	int* data = v.data();
	data[0] = 10;
	front = v.front();
	CHECK(front == 10);
}

TEST_CASE("[Vector] vector Capacity functions")
{
	Vector<int> v = { 1, 2, 3, 4, 5 };

	size_t size = v.size();
	CHECK(size == 5);

	CHECK(v.empty() == false);

	CHECK(v.max_size() == 1024);
}

TEST_CASE("[Vector] vector Modifiers functions")
{
	Vector<int> v = { 1, 2, 3, 4, 5 };

	CHECK(v.size() == 5);

	v.clear();
	CHECK(v.size() == 0);

	for (int i = 0; i < 1024; ++i)
		v.push_back(int(i));
	
	CHECK(v.size() == 1024);

	v.push_back(1024);
	CHECK(v.max_size() == 2 * 1024);
	
	for (size_t i = 0; i < 1024; ++i)
		v.pop_back();

	CHECK(v.front() == 0);
}