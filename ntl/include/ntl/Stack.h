#include<initializer_list>
#include <assert.h>

namespace ntl
{
	template <typename T>
	class Stack
	{
	public:
		Stack() = default;
		Stack(const Stack<T>& other) = default;
		Stack(Stack<T>&& other) = default;
		Stack<T>& operator=(const Stack<T>& other) = default;
		Stack<T>& operator=(Stack<T>&& other) = default;
		~Stack() = default;

		T& top();
		
		bool empty();
		size_t size();
		void clear();

		void push(const T& val);
		void pop();

	private:
		constexpr static size_t MAX_CAPACITY = 1024;
		T _data[MAX_CAPACITY];
		size_t _size = 0;
		int _index = -1;
	};

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
		assert(_size != MAX_CAPACITY && "Stack is full");

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