#include <iostream>
#include <assert.h>

#include "Queue.h"

namespace ntl
{
	template <typename T>
	class Node
	{
	public:
		Node() = default;
		Node(const T& val) noexcept
		{
			this->data = val;
			this->left = nullptr;
			this->right = nullptr;
		}

		T data = T{};
		Node<T>* left = nullptr;
		Node<T>* right = nullptr;
	};

	enum class TRAVERSE_ORDER
	{
		PRE_ORDER,
		IN_ORDER,
		POST_ORDER,
		LEVEL_ORDER
	};

	template<typename T>
	class BST
	{
	public:
		BST() = default;
		~BST();

		bool find(const T& val);
		void insert(const T& val);
		void traverse(TRAVERSE_ORDER order);
		T erase(const T& val);
		void clear();
		bool empty();
		bool hasError();
		size_t size();

	private:
		void preorder(Node<T>* root, int level);
		void postorder(Node<T>* root, int level);
		void inorder(Node<T>* root, int level);
		void levelOrder(Node<T>* root);
		Node<T>* findNode(const T& val);
		Node<T>* findParent(const T& val);
		bool isLeaf(Node<T>* node);
		bool isParentWithOneChild(Node<T>* node);
		Node<T>* getMinimum(Node<T>* node);
		Node<T>* getMaximum(Node<T>* node);
		void destroyNode(Node<T> *node);

	private:
		Node<T>* _root = nullptr;
		bool _error = false;
		size_t _size = 0;

	};

	template<typename T>
	BST<T>::~BST()
	{
		clear();
	}

	// Helper Fucntions

	template<typename T>
	void BST<T>::preorder(Node<T>* root, int level)
	{
		if (root == nullptr)
			return;

		std::cout << "Value = " << root->data << "  Level = " << level << std::endl;
		preorder(root->left, level + 1);
		preorder(root->right, level + 1);
	}

	template<typename T>
	void BST<T>::postorder(Node<T>* root, int level)
	{
		if (root == nullptr)
			return;

		postorder(root->left, level + 1);
		postorder(root->right, level + 1);
		std::cout << "Value = " << root->data << "  Level = " << level << std::endl;
	}

	template<typename T>
	void BST<T>::inorder(Node<T>* root, int level)
	{
		if (root == nullptr)
			return;

		inorder(root->left, level + 1);
		std::cout << "Value = " << root->data << "  Level = " << level << std::endl;
		inorder(root->right, level + 1);
	}

	template<typename T>
	void BST<T>::levelOrder(Node<T>* root)
	{
		using namespace ntl;

		Queue<Node<T>*> queue;
		queue.push(root);

		while (!queue.empty())
		{
			Node<T>* it = queue.front();
			queue.pop();

			if (it != nullptr)
			{
				std::cout << "Value = " << it->data <<std::endl;
				queue.push(it->left);
				queue.push(it->right);
			}
		}
	}

	template<typename T>
	Node<T>* BST<T>::findNode(const T& val)
	{
		Node<T>* it = this->_root;
		while (it != nullptr && it->data != val)
		{
			if (val < it->data)
				it = it->left;
			else
				it = it->right;
		}
		return it;
	}

	template<typename T>
	Node<T>* BST<T>::findParent(const T& val)
	{
		Node<T>* parent = nullptr;
		Node<T>* it = this->_root;

		while (it != nullptr && it->data != val)
		{
			parent = it;
			if (val < it->data)
				it = it->left;
			else
				it = it->right;
		}
		return parent;
	}

	template<typename T>
	bool BST<T>::isLeaf(Node<T>* node)
	{
		return node->left == nullptr && node->right == nullptr;
	}

	template<typename T>
	bool BST<T>::isParentWithOneChild(Node<T>* node)
	{
		return (node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr);
	}

	template <class T>
	Node<T>* BST<T>::getMinimum(Node<T>* node)
	{
		Node<T>* it = node;
		while (it->left != nullptr)
			it = it->left;
		return it;
	}

	template<typename T>
	Node<T>* BST<T>::getMaximum(Node<T>* node)
	{
		Node<T>* it = node;
		while (it->right != nullptr)
			it = it->right;
		return it;
	}

	template<typename T>
	void BST<T>::destroyNode(Node<T> *node)
	{
		if (node == nullptr)
			return;

		destroyNode(node->left);
		destroyNode(node->right);
		delete node;
		--_size;
	}
	// API

	template<typename T>
	bool BST<T>::find(const T& val)
	{
		Node<T>* it = findNode(val);

		if (it == nullptr)
			return false;
		else
			return true;
	}

	template<typename T>
	void BST<T>::insert(const T& val)
	{
		Node<T>* node = new Node<T>{ val };

		if (_root == nullptr)
		{
			_root = node;
			++_size;
		}
		else
		{
			Node<T>* it = this->findNode(val);
			if (it == nullptr)
			{
				it = this->findParent(val);
				if (val < it->data)
					it->left = node;
				else
					it->right = node;
			
				_error = false;
				++_size;
			}
			else
				_error = true;
		}	
	}

	template<typename T>
	void BST<T>::traverse(TRAVERSE_ORDER order)
	{
		switch (order)
		{
		case TRAVERSE_ORDER::PRE_ORDER:
			preorder(_root, 0);
			break;
		case TRAVERSE_ORDER::IN_ORDER:
			inorder(_root, 0);
			break;
		case TRAVERSE_ORDER::POST_ORDER:
			postorder(_root, 0);
			break;
		case TRAVERSE_ORDER::LEVEL_ORDER:
			levelOrder(_root);
			break;
		default:
			assert(false && "Invaild order");
			break;
		}
	}
	
	template <typename T>
	T BST<T>::erase(const T& val)
	{
		T v;
		Node<T>* deleted = findNode(val);
		Node<T>* parent = findParent(val);

		if (deleted == nullptr)
			_error = true;
		else if (isLeaf(deleted))
		{
			if (deleted == _root)
				_root = nullptr;
			else
			{
				if (parent->left == deleted)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			}
			v = deleted->data;
			delete deleted;
			--_size;
		}
		else if (isParentWithOneChild(deleted))
		{
			if (deleted == _root)
			{
				if (deleted->left != nullptr)
					_root = deleted->left;
				else
					_root = deleted->right;
			}
			else
			{
				Node<T>* tmp = nullptr;
				if (deleted->left != nullptr)
					tmp = deleted->left;
				else
					tmp = deleted->right;

				if (parent->left == deleted)
					parent->left = tmp;
				else
					parent->right = tmp;
			}
			v = deleted->data;
			delete deleted;
			--_size;
		}
		else
		{
			Node<T>* highestLeftNode = getMaximum(deleted->left);
			v = erase(highestLeftNode->data);
			deleted->data = v;
		}
		return v;
	}

	template<typename T>
	void BST<T>::clear()
	{
		destroyNode(_root);
		_root = nullptr;
	}

	template<typename T>
	bool BST<T>::empty()
	{
		return _size == 0;
	}
	
	template<typename T>
	bool BST<T>::hasError()
	{
		return _error;
	}

	template<typename T>
	size_t BST<T>::size()
	{
		return this->_size;
	}
}