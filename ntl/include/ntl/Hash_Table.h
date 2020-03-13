#include <stdint.h>

namespace ntl
{
	template<typename T>
	struct Hash
	{
		inline size_t
		operator()(T) const
		{
			static_assert(sizeof(T) == 0, "there's no hash function defined for this type");
			return 0;
		}
	};

	template<typename T>
	struct Hash<T*>
	{
		inline size_t
		operator()(T* ptr) const
		{
			return size_t(ptr);
		}
	};

#define TRIVIAL_HASH(TYPE)\
	template<>\
	struct Hash<TYPE>\
	{\
		inline size_t\
		operator()(TYPE value) const\
		{\
			return static_cast<size_t>(value);\
		}\
	}

	TRIVIAL_HASH(char);
	TRIVIAL_HASH(int8_t);
	TRIVIAL_HASH(int16_t);
	TRIVIAL_HASH(int32_t);
	TRIVIAL_HASH(int64_t);
	TRIVIAL_HASH(uint8_t);
	TRIVIAL_HASH(uint16_t);
	TRIVIAL_HASH(uint32_t);
	TRIVIAL_HASH(uint64_t);

#undef TRIVIAL_HASH


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

	template<typename Key, typename Value, typename Function = Hash <Key>>
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

	template<typename Key, typename Value, typename Function = Hash <Key>>
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

	template<typename Key, typename Value, typename Function = Hash <Key>>
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

	template<typename Key, typename Value, typename Function = Hash <Key>>
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

	template<typename Key, typename Value, typename Function = Hash <Key>>
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

	template<typename Key, typename Value, typename Function = Hash <Key>>
	size_t Hash_Table<Key, Value, Function>::size()
	{
		return _size;
	}
}