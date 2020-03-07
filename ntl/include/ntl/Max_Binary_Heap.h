#include <math.h>
#include <algorithm>
#include <assert.h>

namespace ntl
{
	template<typename T>
	class Max_Binary_Heap
	{
	public:
		Max_Binary_Heap() = default;
		Max_Binary_Heap(const Max_Binary_Heap<T>& other) = default;
		Max_Binary_Heap(Max_Binary_Heap<T>&& other) = default;
		Max_Binary_Heap<T>& operator=(const Max_Binary_Heap<T>& other) = default;
		Max_Binary_Heap<T>& operator=(Max_Binary_Heap<T>&& other) = default;
		~Max_Binary_Heap() = default;
	
		void insert(const T& val);
		T& getMaximum();
		size_t size();

	private:
		size_t parent(size_t index);
		size_t left(size_t index);
		size_t right(size_t index);
		void maxHeapify(size_t index);
	private:
		constexpr static size_t MAX_SIZE = 1024;
		T _data[MAX_SIZE];
		size_t _size = 0;
	};

	// Helper Fucntions
	template<typename T>
	size_t Max_Binary_Heap<T>::parent(size_t index)
	{
		return std::floor((index - 1) / 2);
	}
	
	template<typename T>
	size_t Max_Binary_Heap<T>::left(size_t index)
	{
		return 2 * index + 1;
	}
	
	template<typename T>
	size_t Max_Binary_Heap<T>::right(size_t index)
	{
		return 2 * index + 2;
	}

	template<typename T>
	void Max_Binary_Heap<T>::maxHeapify(size_t index)
	{
		size_t left_idx = left(index);

		size_t right_idx = right(index);

		size_t largest_idx = index;

		if (left_idx < _size && _data[left_idx] > _data[largest_idx])
			largest_idx = left_idx;

		if (right_idx < _size && _data[right_idx] > _data[largest_idx])
			largest_idx = right_idx;

		if (largest_idx != index)
		{
			std::swap(_data[index], _data[largest_idx]);
			maxHeapify(largest_idx);
		}
	}

	// API

	template<typename T>
	void Max_Binary_Heap<T>::insert(const T& val)
	{
		assert(_size != MAX_SIZE && "Heap is full");

		_data[_size] = val;
		++_size;
		
		size_t idx = _size - 1;

		while (idx > 0 && _data[parent(idx)] < _data[idx])
		{
			std::swap(_data[parent(idx)], _data[idx]);
			idx = parent(idx);
		}
	}

	template<typename T>
	T& Max_Binary_Heap<T>::getMaximum()
	{
		T item = _data[0];

		_data[0] = _data[_size - 1];
		--_size;

		maxHeapify(0);

		return item;
	}

	template<typename T>
	size_t Max_Binary_Heap<T>::size()
	{
		return _size;
	}
}