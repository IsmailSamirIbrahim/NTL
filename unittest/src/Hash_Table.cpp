#include <doctest/doctest.h>

#include <ntl/Hash_Table.h>

#include <string>

using namespace ntl;
using namespace std;

TEST_CASE("[Hash Tabel]: inset function")
{
	Hash_Table<int, string> map;

	map.insert(1, "ismail");
	map.insert(2, "samir");
	map.insert(3, "ismail");

	CHECK(map.size() == 3);
}

TEST_CASE("[Hash Tabel]: erase function")
{
	Hash_Table<int, string> map;

	map.insert(1, "ismail");
	map.insert(2, "samir");
	map.insert(3, "ismail");

	CHECK(map.size() == 3);

	map.erase(3);
	
	CHECK(map.size() == 2);

	CHECK(map.find(3, "ismail") == false);



}