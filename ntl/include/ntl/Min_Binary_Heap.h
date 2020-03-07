#include <math.h>
#include <algorithm>
#include <assert.h>

namespace ntl
{
	template<typename T>
	class Min_Binary_Heap
	{
	public:
		Min_Binary_Heap() = default;
		Min_Binary_Heap(const Min_Binary_Heap<T>& other) = default;
		Min_Binary_Heap(Min_Binary_Heap<T>&& other) = default;
		Min_Binary_Heap<T>& operator=(const Min_Binary_Heap<T>& other) = default;
		Min_Binary_Heap<T>& operator=(Min_Binary_Heap<T>&& other) = default;
		~Min_Binary_Heap() = default;
	
		void insert(const T& val);
		T& getMinimum();
		size_t size();

	private:
		size_t parent(size_t index);
		size_t left(size_t index);
		size_t right(size_t index);
		void minHeapify(size_t index);
	private:
		constexpr static size_t MAX_SIZE = 1024;
		T _data[MAX_SIZE];
		size_t _size = 0;
	};

	// Helper Fucntions
	template<typename T>
	size_t Min_Binary_Heap<T>::parent(size_t index)
	{
		return std::floor((index - 1) / 2);
	}
	
	template<typename T>
	size_t Min_Binary_Heap<T>::left(size_t index)
	{
		return 2 * index + 1;
	}
	
	template<typename T>
	size_t Min_Binary_Heap<T>::right(size_t index)
	{
		return 2 * index + 2;
	}

	template<typename T>
	void Min_Binary_Heap<T>::minHeapify(size_t index)
	{
		size_t left_idx = left(index);

		size_t right_idx = right(index);

		size_t lowest_idx = index;

		if (left_idx < _size && _data[left_idx] < _data[lowest_idx])
			lowest_idx = left_idx;

		if (right_idx < _size && _data[right_idx] < _data[lowest_idx])
			lowest_idx = right_idx;

		if (lowest_idx != index)
		{
			std::swap(_data[index], _data[lowest_idx]);
			minHeapify(lowest_idx);
		}
	}

	// API

	template<typename T>
	void Min_Binary_Heap<T>::insert(const T& val)
	{
		assert(_size != MAX_SIZE && "Heap is full");

		_data[_size] = val;
		++_size;

		size_t idx = _size - 1;

		while (idx > 0 && _data[parent(idx)] > _data[idx])
		{
			std::swap(_data[parent(idx)], _data[idx]);
			idx = parent(idx);
		}
	}

	template<typename T>
	T& Min_Binary_Heap<T>::getMinimum()
	{
		T item = _data[0];

		_data[0] = _data[_size - 1];

		--_size;

		minHeapify(0);

		return item;
	}

	template<typename T>
	size_t Min_Binary_Heap<T>::size()
	{
		return _size;
	}
}