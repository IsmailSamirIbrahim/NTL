#include<doctest/doctest.h>

#include <ntl/Stack.h>
#include <memory>

using namespace ntl;

TEST_CASE("[Stack] Stack construction")
{
	Stack<int> s1;
	
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);

	CHECK(s1.size() == 4);

	Stack<int> s2 = s1;
	CHECK(s2.size() == 4);

	Stack<int> s3;
	s3 = s2;
	CHECK(s3.size() == 4);

	Stack<int> s4 = std::move(s3);
}

TEST_CASE("[Stack] push and pop functions")
{
	Stack<int> s1;

	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);

	CHECK(s1.size() == 4);
	CHECK(s1.empty() == false);
	CHECK(s1.top() == 4);

	s1.pop();
	s1.pop();
	s1.pop();

	CHECK(s1.size() == 1);
	CHECK(s1.empty() == false);
	CHECK(s1.top() == 1);
}