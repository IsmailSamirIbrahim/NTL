#include <doctest/doctest.h>

#include <ntl/Trie.h>

using namespace ntl;

TEST_CASE("[Trie]: insertion")
{
	Trie trie{};

	trie.insert("abcd");
	trie.insert("ab");
	trie.insert("abcdef");
	trie.insert("efg");

	CHECK(trie.wordExist("abcd") == true);
	CHECK(trie.wordExist("ab") == true);
}