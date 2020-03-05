#include <initializer_list>

namespace ntl
{
	template<typename T>
	struct List_Node
	{
		List_Node() = default;
		List_Node(T value) noexcept
		{
			data = value ;
			next = nullptr;
			prev = nullptr;
		}

		T data = T{};
		List_Node<T>* next = nullptr;
		List_Node<T>* prev = nullptr;
	};

	template<typename T>
	class List
	{
	public:
		List() = default;

		List(const List<T>& other);
		List<T>& operator=(const List<T>& other);
		
		List(List<T>&& other);
		List<T>& operator=(List<T>&& other);

		List(const std::initializer_list<T>& list);

		~List();

		void assign(const std::initializer_list<T>& list);
		void assign(size_t count, T value);

		void push_front(T value);
		void push_back(T value);

		void pop_front();
		void pop_back();

		void clear();

		bool empty();

		size_t size();

		void erase(size_t index);

		T& front();
		T& back();

	private:
		List_Node<T>* _head = nullptr;
		List_Node<T>* _tail = nullptr;
		size_t _size = 0;
	};

	// Construction
	template<typename T>
	List<T>::List(const List<T>& other)
	{
		auto it1 = other._head;
		auto it2 = this->_head;
		for (size_t i = 0; i < other._size; ++i)
		{
			auto node = new List_Node<T>{ it1->data };
			if (i == 0)
			{
				this->_head = node;
				it2 = node;
			}
			it2->next = node;
			it2 = node;
			it1 = it1->next;

			++this->_size;
		}
	}

	template<typename T>
	List<T>& List<T>::operator=(const List<T>& other)
	{
		auto it1 = other._head;
		auto it2 = this->_head;
		for (size_t i = 0; i < other._size; ++i)
		{
			auto node = new List_Node<T>{ it1->data };
			if (i == 0)
			{
				this->_head = node;
				it2 = node;
			}
			it2->next = node;
			it2 = node;
			it1 = it1->next;

			++this->_size;
		}
		return *this;
	}

	template<typename T>
	List<T>::List(List<T>&& other)
	{
		this->_head = other._head;
		this->_size = other._size;

		other._head = nullptr;
		other._size = 0;
	}

	template<typename T>
	List<T>& List<T>::operator=(List<T>&& other)
	{
		this->_head = other._head;
		this->_size = other._size;

		other._head = nullptr;
		other._size = 0;

		return *this;
	}

	template<typename T>
	List<T>::List(const std::initializer_list<T>& list)
	{
		auto it = list.end();
		--it;
		for (size_t i = 0; i < list.size(); ++i, --it)
			this->push_front(*it);
	}
 
	// Destruction
	template<typename T>
	List<T>::~List()
	{
		clear();
	}


	// API
	template<typename T>
	void List<T>::assign(const std::initializer_list<T>& list)
	{
		auto it = list.begin();
		for (size_t i = 0; i < list.size(); ++i, ++it)
			this->push_back(*it);
	}

	template<typename T>
	void List<T>::assign(size_t count, T value)
	{
		for (size_t i = 0; i < count; ++i)
			this->push_back(value);
	}

	template<typename T>
	void List<T>::push_front(T value)
	{
		auto node = new List_Node<T>{ value };
		if (_size == 0)
		{
			_head = node;
			_tail = node;
			++_size;
			return;
		}

		node->next = _head;
		_head->prev = node;
		_head = node;
		++_size;
	}

	template<typename T>
	void List<T>::push_back(T value)
	{
		auto node = new List_Node<T>{ value };
		if (_size == 0)
		{
			_head = node;
			_tail = node;
			++_size;
			return;
		}

		_tail->next = node;
		node->prev = _tail;
		_tail = node;
		++_size;
	}

	template<typename T>
	void List<T>::pop_front()
	{
		if (this->empty())
			assert(false && "list is empty");

		auto deleted_node = _head;
		_head = _head->next;
		_head->prev = nullptr;
		delete deleted_node;

		--_size;
	}

	template<typename T>
	void List<T>::pop_back()
	{
		if (this->empty())
			assert(false && "list is empty");

		auto deleted_node = _tail;
		_tail = _tail->prev;
		delete deleted_node;
		_tail->next = nullptr;
		--_size;
	}

	template<typename T>
	T& List<T>::front()
	{
		if (this->empty())
			assert(false && "list is empty");

		return _head->data;
	}

	template<typename T>
	T& List<T>::back()
	{
		if (this->empty())
			assert(false && "list is empty");

		return _tail->data;
	}

	template<typename T>
	void List<T>::clear()
	{
		auto it = _head;
		while (it != nullptr)
		{
			_head = _head->next;
			delete it;
			it = _head;
		}
		_tail = nullptr;
		_size = 0;
	}

	template<typename T>
	bool List<T>::empty()
	{
		return _size == 0;
	}

	template<typename T>
	size_t List<T>::size()
	{
		return _size;
	}

	template<typename T>
	void List<T>::erase(size_t index)
	{
		if (this->empty())
			assert(false && "list is empty");

		if (index == 0)
		{
			this->pop_front();
			return;
		}

		auto it = _head;
		while (--index)
			it = it->next;

		auto deleted_node = it->next;
		it->next = deleted_node->next;
		deleted_node->next->prev = it;
		--_size;
	}
}