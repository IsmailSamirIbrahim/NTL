#include <assert.h>
#include <cmath>
#include <algorithm>

#include "ntl/Vector.h"

namespace ntl
{
	template<typename T>
	class Priority_Queue
	{
	public:
		Priority_Queue() = default;
		Priority_Queue(const Priority_Queue& other) = default;
		Priority_Queue(Priority_Queue&& other) = default;
		Priority_Queue& operator=(const Priority_Queue& other) = default;
		Priority_Queue& operator=(Priority_Queue&& other) = default;
		~Priority_Queue() = default;
	
		void push(const T& val);
		void pop();
		T& top();
		size_t size();
		bool empty();

	private:
		size_t parent(size_t index);
		size_t left(size_t index);
		size_t right(size_t index);
		void reheapifyUp(size_t index);
		void reheapifyDown(size_t index);

	private:
		ntl::Vector<T> _data;
		size_t _size = 0;
	};

	// Helper functions

	template<typename T>
	size_t Priority_Queue<T>::parent(size_t index)
	{
		return std::floor((index - 1) / 2);
	}
	
	template<typename T>
	size_t Priority_Queue<T>::left(size_t index)
	{
		return 2 * index + 1;
	}

	template<typename T>
	size_t Priority_Queue<T>::right(size_t index)
	{
		return 2 * index + 2;
	}

	template<typename T>
	void Priority_Queue<T>::reheapifyUp(size_t index)
	{
		while (index != 0 && _data[parent(index)] > _data[index])
		{
			std::swap(_data[parent(index)], _data[index]);
			index = parent(index);
		}
	}

	template<typename T>
	void Priority_Queue<T>::reheapifyDown(size_t index)
	{
		size_t left_idx = left(index);
		size_t right_idx = right(index);
		size_t smallest_idx = index;

		if (left_idx <= _size && _data[left_idx] < _data[smallest_idx])
			smallest_idx = left_idx;

		if (right_idx <= _size && _data[right_idx] < _data[smallest_idx])
			smallest_idx = right_idx;

		if (smallest_idx != index)
		{
			std::swap(_data[index], _data[smallest_idx]);
			reheapifyDown(smallest_idx);
		}
	}

	template<typename T>
	void Priority_Queue<T>::push(const T& val)
	{
		_data.push_back(val);
		++_size;
		size_t idx = _size - 1;
		reheapifyUp(idx);
	}

	template<typename T>
	void Priority_Queue<T>::pop()
	{
		assert(_size != 0 && "Queue is empty");

		_data[0] = _data[_size - 1];
		_data.pop_back();
		--_size;

		reheapifyDown(0);
	}

	template<typename T>
	T& Priority_Queue<T>::top()
	{
		assert(_size != 0 && "Queue is empty");
		return _data[0];
	}

	template<typename T>
	size_t Priority_Queue<T>::size()
	{
		return _size;
	}

	template<typename T>
	bool Priority_Queue<T>::empty()
	{
		return _size == 0;
	}
}