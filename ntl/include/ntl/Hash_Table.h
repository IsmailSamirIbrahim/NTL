namespace ntl
{
	template<typename Key, size_t tabel_size>
	struct Hash
	{
		inline size_t
		operator()(const Key& key) const
		{
			return reinterpret_cast<size_t>(key) % tabel_size;
		}
	};

	template<typename Key, typename Value>
	struct Hash_Node
	{
		Hash_Node(const Key &key, const Value &value)
		{
			this->key = key;
			this->value = value;
			this->next = nullptr;
		}

		Key key;
		Value value;
		Hash_Node<Key, Value>* next = nullptr;
	};

	template<typename Key, typename Value, typename Function = Hash <Key, 1024>>
	class Hash_Table
	{
	public:
		Hash_Table() = default;
		~Hash_Table();

		void insert(const Key& key, const Value& value);
		bool find(const Key& key, const Value& value);
		void erase(const Key& key);
		size_t size();
	private:
		static constexpr size_t TABEL_SIZE = 1024;
		Hash_Node<Key, Value>* table[TABEL_SIZE] = {nullptr};
		Function hasher;
		size_t _size = 0;
	};

	template<typename Key, typename Value, typename Function = Hash <Key, 1024>>
	Hash_Table<Key, Value, Function>::~Hash_Table()
	{
		// destroy all buckets one by one
		for (size_t i = 0; i < 1024; ++i) 
		{
			Hash_Node<Key, Value> *it = table[i];

			while (it != nullptr) {
				Hash_Node<Key, Value> *deleted = it;
				it = it->next;
				delete deleted;
				--_size;
			}

			table[i] = nullptr;
		}
	}

	template<typename Key, typename Value, typename Function = Hash <Key, 1024>>
	void Hash_Table<Key, Value, Function>::insert(const Key& key, const Value& value)
	{
		size_t index = hasher(key);
		Hash_Node<Key, Value>* it = table[index];
		Hash_Node<Key, Value>* prev = nullptr;

		while (it != nullptr && it->key != key)
		{
			prev = it;
			it = it->next;
		}

		if (it == nullptr) 
		{
			it = new Hash_Node<Key, Value>(key, value);

			if (prev == nullptr)
				table[index] = it;
			else
				prev->next = it;
			++_size;
		}
		else
			it->value = value;
	}

	template<typename Key, typename Value, typename Function = Hash <Key, 1024>>
	bool Hash_Table<Key, Value, Function>::find(const Key& key, const Value& value)
	{
		size_t index = hasher(key);

		Hash_Node<Key, Value>* it = table[index];

		while (it != nullptr && it->key != key)
			it = it->next;

		if (it == nullptr)
			return false;
		else
			return true;

	}

	template<typename Key, typename Value, typename Function = Hash <Key, 1024>>
	void Hash_Table<Key, Value, Function>::erase(const Key& key)
	{
		size_t index = hasher(key);
		Hash_Node<Key, Value>* it = table[index];
		Hash_Node<Key, Value>* prev = nullptr;

		while (it != nullptr && it->key != key)
		{
			prev = it;
			it = it->next;
		}

		if (it == nullptr)
			return;

		if (prev == nullptr)
			table[index] = it->next;
		else
		prev->next = it->next;
		
		delete it;
		--_size;
	}

	template<typename Key, typename Value, typename Function = Hash <Key, 1024>>
	size_t Hash_Table<Key, Value, Function>::size()
	{
		return _size;
	}
}