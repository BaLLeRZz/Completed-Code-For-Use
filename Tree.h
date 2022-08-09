#pragma once
#include <iostream>
#include <vector>
#include <string>

class Tree
{
private:
	int value{};
	std::vector<Tree> children{};
	std::vector<Tree> direct_children{};
	void copy(const Tree& other);
	const bool insert_helper(const Tree& node, bool helper);
	void remove_helper(const Tree& node, size_t count);
	std::string print_helper(const std::vector<Tree>& subtrees, std::string result, size_t count) const;
	const bool contains_helper(const std::vector<Tree>& subtrees, const std::vector<Tree>& other_subtrees);
public:
	Tree(const int value);
	Tree(const Tree& other);
	~Tree();
	Tree& operator=(const Tree& other);
	const bool operator==(const Tree& other) const;

	const int get_value() const;
	const std::vector<Tree> get_children() const;
	const std::vector<Tree> get_direct_children() const;
	const bool insert(const int value);
	const bool insert(const Tree& node);
	const bool remove(const int value);
    const bool remove(const Tree& node);
	const bool contains(const Tree& node);
	void print() const;
};

void Tree::copy(const Tree& other)
{
	this->value = other.value;
	this->children = other.children;
	this->direct_children = other.direct_children;
}

const bool Tree::insert_helper(const Tree& node, bool helper)
{
	size_t size = this->direct_children.size();
	for (size_t i = 0; i < size; i++)
	{
		if (this->direct_children.at(i).value == node.value && helper)
			return false;
	}

	if (helper)
	{
		this->direct_children.push_back(node);
		this->children.push_back(node);
	}
	else
		this->children.push_back(node);

	helper = false;
	for (Tree child : node.direct_children)
		this->insert_helper(child, helper);

	return true;
}

void Tree::remove_helper(const Tree& node, size_t count)
{
	for (size_t i = 0; i < node.children.size(); i++)
		this->children.erase(this->children.begin() + count);

	this->children.erase(this->children.begin() + count);
}

std::string Tree::print_helper(const std::vector<Tree>& subtrees, std::string result, size_t count) const
{
	if (count == this->children.size())
		return result;

	size_t size = subtrees.size(), size_children{};
	result.append("| ");
	if (count == 0)
	{
		std::cout << "| " << this->value << " |" << std::endl;
		for (Tree child : subtrees)
			result.append(std::to_string(child.value) + " ");

		result.append("|\n| ");
	}

	std::vector<Tree> lower_levels{};
	for (size_t i = 0; i < size; i++)
	{
		size_children = subtrees[i].direct_children.size();
		for (size_t j = 0; j < size_children; j++)
		{
			result.append(std::to_string(subtrees[i].direct_children[j].value) + " ");
			lower_levels.push_back(subtrees[i].direct_children[j]);
		}
		result.append("| ");
	}

	count += size;
	if (count > 0)
		result.append("\n");

	return this->print_helper(lower_levels, result, count);
}

const bool Tree::contains_helper(const std::vector<Tree>& subtrees, const std::vector<Tree>& other_subtrees)
{
	if (subtrees.size() != other_subtrees.size())
		return false;

	size_t size = subtrees.size(), size_children{};
	bool flag = true;
	for (size_t i = 0; i < size; i++)
	{
		flag = false;
		for (size_t j = 0; j < size; j++)
		{
			if (subtrees[i] == other_subtrees[j])
			{
				flag = true;
				break;
			}
		}

		if (!flag)
			return false;
	}

	std::vector<Tree> lower_levels1{}, lower_levels2{};
	for (size_t i = 0; i < size; i++)
	{
		size_children = subtrees[i].direct_children.size();
		for (size_t j = 0; j < size_children; j++)
			lower_levels1.push_back(subtrees[i].direct_children[j]);
	}

	for (size_t i = 0; i < size; i++)
	{
		size_children = other_subtrees[i].direct_children.size();
		for (size_t j = 0; j < size_children; j++)
			lower_levels2.push_back(other_subtrees[i].direct_children[j]);
	}

	if (other_subtrees.empty())
		return true;

	return this->contains_helper(lower_levels1, lower_levels2);
}

Tree::Tree(const int value)
{
	this->value = value;
}

Tree::Tree(const Tree& other)
{
	this->copy(other);
}

Tree::~Tree()
{
	
}

Tree& Tree::operator=(const Tree& other)
{
	if (this != &other)
		this->copy(other);
	
	return *this;
}

const bool Tree::operator==(const Tree& other) const
{
	if (this->value != other.value)
		return false;

	size_t size_all = this->children.size();
	if (size_all != other.children.size())
		return false;

	for (size_t i = 0; i < size_all; i++)
		if(this->children[i].value != other.children[i].value)
			return false;
	
	size_t size_direct = this->direct_children.size();
	if (size_direct != other.direct_children.size())
		return false;

	for (size_t i = 0; i < size_direct; i++)
		if (this->direct_children[i].value != other.direct_children[i].value)
			return false;

	return true;
}

const int Tree::get_value() const
{
	return this->value;
}

const std::vector<Tree> Tree::get_children() const
{
	return this->children;
}

const std::vector<Tree> Tree::get_direct_children() const
{
	return this->direct_children;
}

const bool Tree::insert(const int value)
{
	for (Tree child : this->direct_children)
		if (child.value == value)
			return false;
	
	this->direct_children.push_back(Tree(value));
	this->children.push_back(Tree(value));

	return true;
}

const bool Tree::insert(const Tree& node)
{
	if (this->insert_helper(node, true))
		return true;

	return false;
}

const bool Tree::remove(const int value)
{
	size_t count{}, numbers{};
	for (Tree child : this->children)
	{
		if (child.value == value)
			numbers++;
	}

	if (numbers == 0)
		return false;

	for (Tree child_direct : this->direct_children)
	{
		if (child_direct.value == value)
		{
			this->direct_children.erase(this->direct_children.begin() + count);
			break;
		}

		count++;
	}

	while (numbers > 0)
	{
		count = 0;
		for (Tree child : this->children)
		{
			if (child.value == value)
			{
				this->remove_helper(child, count);
				break;
			}

			count++;
		}

		numbers--;
	}
	return true;
}

const bool Tree::remove(const Tree& node)
{
	size_t count{}, numbers{}, size = this->children.size();
	for (Tree child : this->children)
	{
		if (child == node)
			numbers++;
	}

	if (numbers == 0)
		return false;

	for (Tree child_direct : this->direct_children)
	{
		if (child_direct == node)
			this->direct_children.erase(this->direct_children.begin() + count);

		count++;
	}

	while (numbers > 0)
	{
		count = 0;
		for (Tree child : this->children)
		{
			if (child == node)
			{
				this->remove_helper(child, count);
				break;
			}

			count++;
		}

		numbers--;
	}
	return false;
}

const bool Tree::contains(const Tree& node)
{
	for (Tree child : this->children)
	{
		if (child.value == node.value)
		{
			if (this->contains_helper(child.direct_children, node.direct_children))
				return true;
		}
	}

	return false;
}

void Tree::print() const
{
	std::cout << this->print_helper(this->direct_children, "", 0);
}
