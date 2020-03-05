#include<initializer_list>
#include <assert.h>

namespace ntl
{
	template <typename T>
	class Queue
	{
	public:
		Queue() = default;
		Queue(const Queue<T>& other) = default;
		Queue(Queue<T>&& other) = default;
		Queue<T>& operator=(const Queue<T>& other) = default;
		Queue<T>& operator=(Queue<T>&& other) = default;
		~Queue() = default;

		T& front();
		
		size_t size();

		bool empty();
		void clear();

		void push(const T& val);
		void pop();

	private:
		constexpr static size_t MAX_CAPACITY = 1024;
		T _data[MAX_CAPACITY];
		size_t _size = 0;
		int _front = -1;
		int _rear = -1;
	};

	template<typename T>
	T& Queue<T>::front()
	{
		assert(!this->empty() && "Queue is empty");

		return this->_data[_front];
	}

	template<typename T>
	size_t Queue<T>::size()
	{
		return this->_size;
	}

	template<typename T>
	bool Queue<T>::empty()
	{
		return _front == _rear == -1;
	}

	template<typename T>
	void Queue<T>::clear()
	{
		this->_front = -1;
		this->_rear = -1;
	}

	template<typename T>
	void Queue<T>::push(const T& val)
	{
		assert((_rear + 1) % MAX_CAPACITY != _front && "Queue is full");

		if (_rear == -1)
			_front = _rear = 0;
		else
			_rear = (_rear + 1) % MAX_CAPACITY;
		
		this->_data[_rear] = val;

		++_size;
	}

	template<typename T>
	void Queue<T>::pop()
	{
		assert(!this->empty() && "Queue is empty");

		if (_front == _rear)
			_front = _rear = -1;
		else
			_front = (_front + 1) % MAX_CAPACITY;

		--_size;
	}
}