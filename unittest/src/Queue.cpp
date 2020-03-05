#include<doctest/doctest.h>

#include <ntl/Queue.h>

using namespace ntl;

TEST_CASE("[Queue] push and pop functions")
{
	Queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	CHECK(q.size() == 4);
	CHECK(q.empty() == false);
	CHECK(q.front() == 1);

	q.pop();
	q.pop();
	q.pop();

	CHECK(q.size() == 1);
	CHECK(q.empty() == false);
	CHECK(q.front() == 4);
}