#pragma once

#include <stdint.h>
#include <malloc.h>
#include <assert.h>

namespace ntl
{
	template<typename T>
	struct INode
	{
		T data;
		INode<T>* next;
	};

	template<typename T>
	using Node = INode<T>*;

	template<typename T>
	struct SLList
	{
		Node<T> head;
		Node<T> tail;
		size_t count;

		T&
		operator[](size_t idx)
		{
			assert(idx < count);

			Node<T> curr = head;
			for (size_t i = 0; i < idx; ++i)
				curr = curr->next;

			return curr->data;
		}

		const T&
		operator[](size_t ix) const
		{
			assert(idx < count);

			Node<T> curr = head;
			for (size_t i = 0; i < idx; ++i)
				curr = curr->next;

			return curr->data;
		}
	};

	// Constructtion and destruction
	template<typename T>
	inline static SLList<T>
	sllist_new()
	{
		SLList<T> self{};

		self.head = nullptr;
		self.tail = nullptr;
		self.count = 0;

		return self;
	}

	template<typename T>
	inline static void destruct(T& value) { value.~T(); }
	inline static void destruct(char&) {}
	inline static void destruct(uint8_t&) {}
	inline static void destruct(uint16_t&) {}
	inline static void destruct(uint32_t&) {}
	inline static void destruct(uint64_t&) {}
	inline static void destruct(int8_t&) {}
	inline static void destruct(int16_t&) {}
	inline static void destruct(int32_t&) {}
	inline static void destruct(int64_t&) {}
	inline static void destruct(float&) {}
	inline static void destruct(double&) {}
	inline static void destruct(long double&) {}

	template<typename T>
	inline static void
	sllist_free(SLList<T>& self)
	{
		while (self.head != nullptr)
		{
			Node<T> tmp = self.head;
			self.head = tmp->next;
			destruct(tmp->data);
			::free(tmp);
			--self.count;
		}
		self.tail = nullptr;
	}

	template<typename T>
	inline static void
	destruct(SLList<T>& self)
	{
		sllist_free(self);
	}
	//----------------------------------------------------------

	// Element access
	template<typename T>
	inline static T&
	sllist_front(const SLList<T>& self)
	{
		return self.head->data;
	}

	template<typename T>
	inline static const T&
	sllist_front(const SLList<T>& self)
	{
		return self.head->data;
	}

	template<typename T>
	inline static T&
	sllist_back(const SLList<T>& self)
	{
		return self.tail->data;
	}

	template<typename T>
	inline static const T&
	sllist_back(const SLList<T>& self)
	{
		return self.tail->data;
	}
	//----------------------------------------------------------

	// Capacity
	template<typename T>
	inline static const bool
	sllist_empty(const SLList<T>& self)
	{
		return self.count == 0;
	}

	template<typename T>
	inline static const size_t
	sllist_size(const SLList<T>& self)
	{
		return self.count;
	}
	//----------------------------------------------------------

	// Modifiers
	template<typename T, typename R>
	inline static void
	sllist_push_front(SLList<T>& self, const R& value)
	{
		Node<T> node = (Node<T>)::malloc(sizeof(INode<T>));
		node->data = value;
		node->next = self.head;
		self.head = node;

		if (self.count == 0)
			self.tail = node;

		++self.count;
	}

	template<typename T>
	inline static void
	sllist_pop_front(SLList<T>& self)
	{
		if (self.count == 0)
			return;

		Node<T> deleted = self.head;
		self.head = deleted->next;
		destruct(deleted->data);
		::free(deleted);
		--self.count;

		if (self.count == 0)
		{
			self.head = nullptr;
			self.tail = nullptr;
		}
	}

	template<typename T, typename R>
	inline static void
	sllist_push_back(SLList<T>& self, const R& value)
	{
		Node<T> node = (Node<T>)::malloc(sizeof(INode<T>));
		node->data = value;
		node->next = nullptr;

		if (self.count != 0)
			self.tail->next = node;

		self.tail = node;

		if (self.count == 0)
			self.head = node;

		++self.count;
	}

	template<typename T>
	inline static void
	sllist_pop_back(SLList<T>& self)
	{
		if (self.count == 0)
			return;

		Node<T> tmp = self->head;
		while (tmp->next != nullptr && tmp->next != self.tail)
			tmp = tmp->next;

		Node<T> deleted = self.tail;
		self.tail = tmp;
		destruct(deleted->data);
		::free(deleted);
		--self.count;

		if (self.count == 0)
		{
			self.head = nullptr;
			self.tail = nullptr;
		}
	}

	template<typename T, typename R>
	inline static void
	sllist_insert(SLList<T>& self, uint32_t idx, const R& value)
	{
		assert(idx < self.count);

		if (idx == 0)
			sllist_push_front(self, value);
		else if (idx == self.count - 1)
			sllist_push_back(self, value);
		else
		{
			Node<T> curr = self.head;
			size_t i = 0;
			while (++i < idx)
				curr = curr->next;

			Node<T> node = (Node<T>)::malloc(sizeof(INode<T>));
			node->data = value;
			node->next = curr->next;
			curr->next = node;
			++self.count;
		}
	}

	template<typename T, typename R>
	inline static void
	sllist_erase(SLList<T>& self, uint32_t idx)
	{
		assert(idx < self.count);

		if (idx == 0)
			sllist_pop_front(self);
		else if (idx == self.count - 1)
			sllist_pop_back(self);
		else
		{
			Node<T> curr = self.head;
			size_t i = 0;
			while (++i < idx)
				curr = curr->next;

			Node<T> deleted = curr->next;
			curr->next = deleted->next;
			destruct(deleted->data);
			::free(deleted);
			--self.count;
		}
	}

	template<typename T, typename R>
	inline static void
	sllist_clear(SLList<T>& self)
	{
		sllist_free(self);
	}

} //namespace end