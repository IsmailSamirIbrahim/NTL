#include <doctest/doctest.h>

#include <ntl/Priority_Queue.h>

using namespace ntl;

TEST_CASE("[priority queue] push function")
{
	Priority_Queue<int> q;

	q.push(4);
	q.push(8);
	q.push(6);
	q.push(7);
	q.push(10);
	q.push(15);
	q.push(20);

	CHECK(q.size() == 7);
}

TEST_CASE("[priority queue] pop function")
{
	Priority_Queue<int> q;

	q.push(4);
	q.push(8);
	q.push(6);
	q.push(7);
	q.push(10);
	q.push(15);
	q.push(20);

	q.pop();
	q.pop();
	q.pop();

	CHECK(q.size() == 4);
}

TEST_CASE("[priority queue] top function")
{
	Priority_Queue<int> q;

	q.push(4);
	q.push(8);
	q.push(6);
	q.push(7);
	q.push(10);
	q.push(15);
	q.push(20);

	CHECK(q.size() == 7);
	CHECK(q.top() == 4);

	q.pop();
	CHECK(q.top() == 6);

}