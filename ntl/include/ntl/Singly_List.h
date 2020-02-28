#include <initializer_list>

namespace ntl
{
	template<typename T>
	struct INode
	{
		T data = T{ 0 };
		INode<T>* next = nullptr;

		INode() = default;
		explicit INode(T value)
		{
			data = value ;
			next = nullptr;
		}
	};

	template<typename T>
	using Node = INode<T>*;

	template<typename T>
	class Single_List
	{
	public:
		Single_List() = default;
		~Single_List();

		T& front();

		bool empty();
		size_t size();

		void push_front(T value);
		void pop_front();

		void assign(const std::initializer_list<T>& list);
		void assign(size_t count, T value);
		void insert(size_t index, T value);

		void erase(size_t index);

		void clear();

	private:
		Node<T> _head = nullptr;
		size_t _size = 0;
	};

	template<typename T>
	Single_List<T>::~Single_List()
	{
		this->clear();
	}

	template<typename T>
	T& Single_List<T>::front()
	{
		return _head->data;
	}

	template<typename T>
	bool Single_List<T>::empty()
	{
		return _size == 0;
	}

	template<typename T>
	size_t Single_List<T>::size()
	{
		return _size;
	}

	template<typename T>
	void Single_List<T>::push_front(T value)
	{
		Node<T> node = new INode<T>(value);
		node->next = _head;
		_head = node;
		++_size;
	}

	template<typename T>
	void Single_List<T>::pop_front()
	{
		if (_size == 0)
			return;

		Node<T> deleted_node = _head;
		_head = deleted_node->next;

		delete deleted_node;
		--_size;
	}

	template<typename T>
	void Single_List<T>::assign(size_t count, T value)
	{
		for (size_t i = 0; i < count; ++i)
			this->push_front(value);
	}

	template<typename T>
	void Single_List<T>::assign(const std::initializer_list<T>& list)
	{
		for (const auto& e : list)
			this->push_front(e);
	}

	template<typename T>
	void Single_List<T>::insert(size_t index, T value)
	{
		if (index == 0)
		{
			this->push_front(value);
			return;
		}

		Node<T> it = _head;
		while (--index)
			it = it->next;

		Node<T> node = new INode<T>{ value };
		node->next = it->next;
		it->next = node;
		++_size;
	}

	template<typename T>
	void Single_List<T>::erase(size_t index)
	{
		if (_size == 0)
			return;

		if (index == 0)
		{
			this->pop_front();
			return;
		}

		Node<T> it = _head;
		while (--index)
			it = it->next;

		Node<T> deleted_node = it->next;
		it->next = deleted_node->next;
		delete deleted_node;

		--_size;
	}

	template<typename T>
	void Single_List<T>::clear()
	{
		if (_size == 0)
			return;

		Node<T> it = _head;
		while (_head != nullptr)
		{
			it = _head;
			_head = it->next;
			delete it;
			--_size;
		}
	}
}