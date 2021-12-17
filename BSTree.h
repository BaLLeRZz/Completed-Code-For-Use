#pragma once
#include<iostream>
#include<vector>

template<class T>
class BSTree
{
private:
	T value{};
	BSTree<T>* left{};
	BSTree<T>* right{};
	void copy(const BSTree<T>& other);
	void erase();
	BSTree<T>* recursive_insert(BSTree<T>* tree, const T& value);
	BSTree<T>* minimal_value(BSTree<T>* tree);
	BSTree<T>* recursive_remove(BSTree<T>* tree, const T& value);
public:
	BSTree(const T& value) : value(value) {};
	BSTree(const BSTree<T>& other);
	BSTree<T>& operator=(const BSTree<T>& other);
	~BSTree();
	
	void insert_value(const T& value);
	void remove_value(const T& value);

	std::vector<T> inorder() const;
	std::vector<T> preorder() const;
	std::vector<T> postorder() const;
};

template<class T>
void BSTree<T>::copy(const BSTree<T>& other)
{
	this->value = other.value;
	if (other.left)
		this->left = new BSTree<T>(*other.left);

	if (other.right)
		this->right = new BSTree<T>(*other.right);
}

template<class T>
void BSTree<T>::erase()
{
	delete this->left;
	delete this->right;
}

template<class T>
BSTree<T>* BSTree<T>::recursive_insert(BSTree<T>* tree, const T& value)
{
	if (!tree)
		return new BSTree<T>(value);

	if (tree->value < value)
		tree->right = this->recursive_insert(tree->right, value);

	else
		tree->left = this->recursive_insert(tree->left, value);

	return tree;
}

template<class T>
BSTree<T>* BSTree<T>::minimal_value(BSTree<T>* tree)
{
	BSTree<T>* current = tree;
	while (current && current->left)
		current = current->left;

	return current;
}

template<class T>
BSTree<T>* BSTree<T>::recursive_remove(BSTree<T>* tree, const T& value)
{
	if (!tree)
		return nullptr;

	if (tree->value < value)
		tree->right = this->recursive_remove(tree->right, value);
	else
	if (tree->value > value)
		tree->left = this->recursive_remove(tree->left, value);
	else
	{
		if (!tree->left && !tree->right)
		{
			delete tree;
			return nullptr;
		}
		
		if (!tree->left)
		{
			BSTree<T>* temp = tree->right;
			delete tree;
			return temp;
		}

		if (!tree->right)
		{
			BSTree<T>* temp = tree->left;
			delete tree;
			return temp;
		}

		BSTree<T>* node = this->minimal_value(tree->right);
		tree->value = node->value;
		this->recursive_remove(tree->right, node->value);
	}

	return tree;
}

template<class T>
BSTree<T>::BSTree(const BSTree<T>& other)
{
	this->copy(other);
}

template<class T>
BSTree<T>& BSTree<T>::operator=(const BSTree<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

template<class T>
BSTree<T>::~BSTree()
{
	this->erase();
}

template<class T>
void BSTree<T>::insert_value(const T& value)
{
	this->recursive_insert(this, value);
}

template<class T>
void BSTree<T>::remove_value(const T& value)
{
	this->recursive_remove(this, value);
}

template<class T>
std::vector<T> BSTree<T>::inorder() const
{
	std::vector<T> elements;
	if (this->left)
		elements = this->left->inorder();

	elements.push_back(this->value);
	if (this->right)
	{
		std::vector<T> right_tree = this->right->inorder();
		elements.insert(elements.end(), right_tree.begin(), right_tree.end());
	}
	return elements;
}

template<class T>
std::vector<T> BSTree<T>::preorder() const
{
	std::vector<T> elements;
	elements.push_back(this->value);
	if (this->left != nullptr)
	{
		std::vector<T> left_tree = this->left->preorder();
		elements.insert(elements.end(), left_tree.begin(), left_tree.end());
	}
	if (this->right != nullptr)
	{
		std::vector<T> right_tree = this->right->preorder();
		elements.insert(elements.end(), right_tree.begin(), right_tree.end());
	}
	return elements;
}

template<class T>
std::vector<T> BSTree<T>::postorder() const
{
	std::vector<T> elements;
	if (this->left != nullptr)
	{
		elements = this->left->postorder();
	}
	if (this->right != nullptr)
	{
		std::vector<T> right_tree = this->right->postorder();
		elements.insert(elements.end(), right_tree.begin(), right_tree.end());
	}
	elements.push_back(this->value);
	return elements;
}
