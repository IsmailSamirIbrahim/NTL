
namespace ntl
{
	const size_t ALPHABET_SIZE = 26;
	struct Trie
	{
		Trie* child[ALPHABET_SIZE] = { nullptr };
		bool isLeaf = false;

		void insert(const char* str);
		bool wordExist(const char* str);
		bool prefixExist(const char* str);
	};

	void Trie::insert(const char* str)
	{
		if (*str == '\0')
			isLeaf = true;
		else
		{
			size_t idx = *str - 'a';
			if (child[idx] == nullptr)
				child[idx] = new Trie{};
			child[idx]->insert(str + 1);
		}
	}

	bool Trie::wordExist(const char* str)
	{
		if (*str == '\0')
			return isLeaf;

		size_t idx = *str - 'a';
		if (child[idx] == nullptr)
			return false;

		return child[idx]->wordExist(str + 1);
	}

	bool Trie::prefixExist(const char* str)
	{
		if (*str == '\0')
			return true;

		size_t idx = *str - 'a';
		if (child[idx] == nullptr)
			return false;

		return child[idx]->wordExist(str + 1);
	}
}