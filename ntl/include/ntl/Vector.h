#include <initializer_list>
#include <assert.h>

namespace ntl
{
	template<typename T>
	class Vector
	{
	public:
		Vector();
		Vector(size_t size);
		Vector(size_t size, const T& val);
		Vector(const std::initializer_list<T>& list);
		Vector(const Vector<T>& other);
		Vector(Vector<T>&& other);
		~Vector();
		Vector<T> operator=(const Vector<T>& other);
		Vector<T> operator=(Vector<T>&& other);

		T& at(size_t index);
		T& front();
		const T& front() const;
		T& back();
		const T& back() const;
		T* data();

		bool empty();
		size_t size();
		size_t max_size();

		void clear();
		void push_back(const T& val);
		void pop_back();
		void resize(size_t new_size);

	private:
		void expande();

	private:
		T* _data;
		size_t _capacity;
		size_t _size;
	};

	template<typename T>
	Vector<T>::Vector()
	{
		this->_capacity= 1024;
		this->_size = 0;
		this->_data = new T[_capacity];
	}

	template<typename T>
	Vector<T>::Vector(size_t size)
	{
		this->_capacity= 1024;
		this->_size = size;
		this->_data = new T[_capacity];
	}

	template<typename T>
	Vector<T>::Vector(size_t size, const T& val)
	{
		this->_capacity= 1024;
		this->_size = size;
		this->_data = new T[_capacity];
		for (size_t i = 0; i < size; ++i)
			this->_data[i] = val;
	}

	template<typename T>
	Vector<T>::Vector(const std::initializer_list<T>& list)
	{
		this->_capacity= 1024;
		this->_size = list.size();
		this->_data = new T[_capacity];

		size_t index = 0;
		for (auto it = list.begin(); it != list.end(); ++it)
			_data[index++] = *it;
	}

	template<typename T>
	Vector<T>::Vector(const Vector<T>& other)
	{
		this->_capacity= other._capacity;
		this->_size = other._size;
		this->_data = new T[this->_capacity];
		for (size_t i = 0; i < this->_size; ++i)
			this->_data[i] = other._data[i];
	}

	template<typename T>
	Vector<T>::Vector(Vector<T>&& other)
	{
		this->_capacity= other._capacity;
		this->_size = other.size;
		this->_data = other._data;

		other._data = nullptr;
		other._size = 0;
		other._capacity= 0;
	}

	template<typename T>
	Vector<T>::~Vector()
	{
		this->_capacity= 0;
		this->_size = 0;
		delete[] this->_data;
	}

	template<typename T>
	Vector<T> Vector<T>::operator=(const Vector<T>& other)
	{
		this->_capacity= other._capacity;
		this->_size = other._size;
		this->_data = new T[this->_capacity];
		for (size_t i = 0; i < this->_size; ++i)
			this->_data[i] = other._data[i];
		
		return *this;
	}

	template<typename T>
	Vector<T> Vector<T>::operator=(Vector<T>&& other)
	{
		this->_capacity= other._capacity;
		this->_size = other._size;
		this->_data = other._data;

		other._data = nullptr;
		other._size = 0;
		other._capacity= 0;

		return *this;
	}

	template<typename T>
	T& Vector<T>::at(size_t index)
	{
		if (index > this->_size - 1)
			assert(false && "index out of range");

		return this->_data[index];
	}

	template<typename T>
	T& Vector<T>::front()
	{
		if (this->empty())
			assert(false && "vector is empty");

		return this->_data[0];
	}

	template<typename T>
	const T& Vector<T>::front() const
	{
		if (this->empty())
			assert(false && "vector is empty");

		return this->_data[0];
	}

	template<typename T>
	T& Vector<T>::back()
	{
		if (this->empty())
			assert(false && "vector is empty");

		return this->_data[this->_size - 1];
	}

	template<typename T>
	const T& Vector<T>::back() const
	{
		if (this->empty())
			assert(false && "vector is empty");

		return this->_data[this->_size - 1];
	}

	template<typename T>
	T* Vector<T>::data()
	{
		return this->_data;
	}

	template<typename T>
	bool Vector<T>::empty()
	{
		return this->_size == 0;
	}

	template<typename T>
	size_t Vector<T>::size()
	{
		return this->_size;
	}

	template<typename T>
	size_t Vector<T>::max_size()
	{
		return this->_capacity;
	}

	template<typename T>
	void Vector<T>::clear()
	{
		this->_size = 0;
	}

	template<typename T>
	void Vector<T>::expande()
	{
		this->_capacity= this->_capacity* 2;
		T* tmp_data = new T[this->_capacity];
		for (size_t i = 0; i < this->size(); ++i)
			tmp_data[i] = this->_data[i];

		delete[] this->_data;

		this->_data = tmp_data;
	}

 	template<typename T>
	void Vector<T>::push_back(const T& val)
	{
		if (this->_capacity <= this->_size)
			expande();

		this->_data[this->_size] = val;
		++this->_size;
	}

	template<typename T>
	void Vector<T>::pop_back()
	{
		if (this->empty())
			assert(false && "vector is empty");

		--this->_size;
	}

	template<typename T>
	void Vector<T>::resize(size_t new_size)
	{
		T* tmp_data = new T[new_size];
		size_t size = new_size < this->_size ? new_size : this->_size;
		for (size_t i = 0; i < size; ++i)
			tmp_data[i] = this->_data[i];

		delete[] this->_data;
		this->_data = tmp_data;
	}
}