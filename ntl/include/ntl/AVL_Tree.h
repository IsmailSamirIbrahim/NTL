#include <algorithm>
namespace ntl
{
	template<typename T>
	struct AVL_Node
	{
		AVL_Node<T>() = default;
		AVL_Node<T>(const T& val)
		{
			this->val = val;
			this->bf = 0;
			this->parent = nullptr;
			this->left = nullptr;
			this->right = nullptr;
		}

		T val = T{};
		int bf = 0;
		AVL_Node<T>* parent = nullptr;
		AVL_Node<T>* left = nullptr;
		AVL_Node<T>* right = nullptr;
	};

	template<typename T>
	class AVL_Tree
	{
	public:
		AVL_Tree() = default;
		~AVL_Tree();

		void insert(const T& val);
		T& erase(const T& val);

	private:
		AVL_Node<T>* findNode(const T& val);
		AVL_Node<T>* findParent(const T& val);
		void rightRotation(AVL_Node<T>* node);
		void leftRotation(AVL_Node<T>* node);
		void updateBalance(AVL_Node<T>* node);
		void rebalance(AVL_Node<T>* node);
		bool isLeaf(AVL_Node<T>* node);
		bool isParentWithOneChild(AVL_Node<T>* node);
		AVL_Node<T>* getMaximum(AVL_Node<T>* node);
	private:
		AVL_Node<T>* _root;
		size_t _size;
	};

	template<typename T>
	AVL_Tree<T>::~AVL_Tree()
	{

	}

	template<typename T>
	AVL_Node<T>* AVL_Tree<T>::findNode(const T& val)
	{
		AVL_Node<T>* it = this->_root;
		while (it != nullptr && it->val != val)
		{
			if (val < it->val)
				it = it->left;
			else
				it = it->right;
		}
		return it;
	}

	template<typename T>
	AVL_Node<T>* AVL_Tree<T>::findParent(const T& val)
	{
		AVL_Node<T>* parent = nullptr;
		AVL_Node<T>* it = this->_root;

		while (it != nullptr && it->val != val)
		{
			parent = it;
			if (val < it->val)
				it = it->left;
			else
				it = it->right;
		}
		return parent;
	}

	template<typename T>
	void AVL_Tree<T>::rightRotation(AVL_Node<T>* y)
	{
		AVL_Node<T>* x = y->left;

		y->left = x->right;
		if (x->right != nullptr)
			y->left->parent = y;

		x->parent = y->parent;
		if (y->parent == nullptr)
			_root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;

		x->right = y;
		y->parent = x;

		// update the balance factor
		y->bf = y->bf - 1 - std::max(0, x->bf);
		x->bf = x->bf - 1 + std::min(0, y->bf);
	}

	template<typename T>
	void AVL_Tree<T>::leftRotation(AVL_Node<T>* x)
	{
		AVL_Node<T>* y = x->right;
		
		x->right = y->left;
		if (y->left != nullptr)
			x->right->parent = x;

		y->parent = x->parent;
		if (x->parent == nullptr)
			_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->left = x;
		x->parent = y;

		// update the balance factor
		x->bf += 1 - std::min(0, y->bf);
		y->bf += 1 + std::max(0, x->bf);
	}

	template<typename T>
	void AVL_Tree<T>::rebalance(AVL_Node<T>* node) 
	{
		if (node->bf == 2)
		{
			if (node->left->bf == -1)
				leftRotation(node->left);

			rightRotation(node);
		}
		else if (node->bf == -2)
		{
			if (node->right->bf == 1)
				rightRotation(node->right);
			leftRotation(node);
		}
	}

	template<typename T>
	void AVL_Tree<T>::updateBalance(AVL_Node<T>* node)
	{
		if (node->bf < -1 || node->bf > 1)
		{
			rebalance(node);
			return;
		}

		if (node->parent != nullptr) 
		{
			if (node == node->parent->left)
				node->parent->bf += 1;

			if (node == node->parent->right)
				node->parent->bf -= 1;

			if (node->parent->bf != 0)
				updateBalance(node->parent);
		}
	}

	template<typename T>
	bool AVL_Tree<T>::isLeaf(AVL_Node<T>* node)
	{
		return node->left == nullptr && node->right == nullptr;
	}

	template<typename T>
	bool AVL_Tree<T>::isParentWithOneChild(AVL_Node<T>* node)
	{
		return (node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr);
	}

	template<typename T>
	AVL_Node<T>* AVL_Tree<T>::getMaximum(AVL_Node<T>* node)
	{
		AVL_Node<T>* it = node;
		while (it->right != nullptr)
			it = it->right;
		return it;
	}

	template<typename T>
	void AVL_Tree<T>::insert(const T& val)
	{
		AVL_Node<T>* node = new AVL_Node<T>{ val };

		if (_root == nullptr)
		{
			_root = node;
			++_size;
		}
		else
		{
			auto it = this->findNode(val);
			if (it == nullptr)
			{
				it = this->findParent(val);
				if (val < it->val)
					it->left = node;
				else
					it->right = node;

				node->parent = it;
				++_size;
			}
		}
		
		// PART 2: re-balance the node if necessary
		updateBalance(node);
	}

	template <typename T>
	T& AVL_Tree<T>::erase(const T& val)
	{
		T v;
		AVL_Node<T>* deleted = findNode(val);
		AVL_Node<T>* parent = findParent(val);

		if (isLeaf(deleted))
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
			updateBalance(deleted->parent);

			v = deleted->val;
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
				AVL_Node<T>* tmp = nullptr;
				if (deleted->left != nullptr)
					tmp = deleted->left;
				else
					tmp = deleted->right;

				if (parent->left == deleted)
					parent->left = tmp;
				else
					parent->right = tmp;
			}
			v = deleted->val;
			delete deleted;
			--_size;
		}
		else
		{
			AVL_Node<T>* highestLeftNode = getMaximum(deleted->left);
			v = erase(highestLeftNode->val);
			deleted->val = v;
		}

		
		return v;
	}

}