#include<initializer_list>
#include <assert.h>

namespace ntl
{
	template <typename T>
	class Stack
	{
	public:
		Stack();
		Stack(const Stack<T>& other);
		Stack(Stack<T>&& other);
		Stack<T>& operator=(const Stack<T>& other);
		Stack<T>& operator=(Stack<T>&& other);
		~Stack();

		T& top();
		
		bool empty();
		size_t size();
		void clear();

		void push(const T& val);
		void pop();

	private:
		void expande();
	private:
		T* _data;
		size_t _size;
		size_t _capacity;
		int _index;
	};

	template<typename T>
	Stack<T>::Stack()
	{
		this->_size = 0;
		this->_index = -1;
		this->_capacity = 1024;
		this->_data = new T[_capacity];
	}

	template<typename T>
	Stack<T>::Stack(const Stack<T>& other)
	{
		this->_size = other._size;
		this->_index = other._index;
		this->_capacity = other._capacity;
		
		this->_data = new T[this->_capacity];
		for (size_t i = 0; i < this->_size; ++i)
			this->_data[i] = other._data[i];
	}
	
	template<typename T>
	Stack<T>::Stack(Stack<T>&& other)
	{
		this->_size = other._size;
		this->_capacity = other._capacity;
		this->_data = other._data;

		other._size = 0;
		other._index = -1;
		other._capacity = 0;
		other._data = nullptr;
	}

	template<typename T>
	Stack<T>& Stack<T>::operator=(const Stack<T>& other)
	{
		this->_size = other._size;
		this->_index = other._index;
		this->_capacity = other._capacity;
		
		this->_data = new T[this->_capacity];
		for (size_t i = 0; i < this->_size; ++i)
			this->_data[i] = other._data[i];
		
		return *this;
	}
	
	template<typename T>
	Stack<T>& Stack<T>::operator=(Stack<T>&& other)
	{
		this->_size = other._size;
		this->_index = other._index;
		this->_capacity = other._capacity;
		this->_data = other._data;

		other._size = 0;
		other._index = -1;
		other._capacity = 0;
		other._data = nullptr;

		return *this;
	}

	template<typename T>
	Stack<T>::~Stack()
	{
		delete[] this->_data;
	}

	template<typename T>
	void Stack<T>::expande()
	{
		this->_capacity = this->_capacity * 2;
		T* tmp_data = new T[this->_capacity];
		for (size_t i = 0; i < this->size(); ++i)
			tmp_data[i] = this->_data[i];

		delete[] this->_data;

		this->_data = tmp_data;
	}

	template<typename T>
	T& Stack<T>::top()
	{
		assert(!this->empty() && "Stack is empty");

		return this->_data[_index];
	}

	template<typename T>
	bool Stack<T>::empty()
	{
		return this->_size == 0;
	}

	template<typename T>
	size_t Stack<T>::size()
	{
		return this->_size;
	}

	template<typename T>
	void Stack<T>::clear()
	{
		this->_size = 0;
		this->_index = -1
	}

	template<typename T>
	void Stack<T>::push(const T& val)
	{
		if (_capacity <= _size)
			expande();

		this->_data[_size] = val;

		++_index;
		++_size;
	}

	template<typename T>
	void Stack<T>::pop()
	{
		assert(!this->empty() && "Stack is empty");

		--this->_size;
		--this->_index;
	}
}