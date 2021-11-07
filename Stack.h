#pragma once
#include<cassert>
#include<iostream>

template<class Type>
class Stack
{
private:
	Type* elements{ new Type[2] };
	size_t size{};
	size_t capacity{ 2 };
	void copy(const Stack<Type>& other);
	void erase();
	void resize();
public:
	Stack() = default;
	Stack(const Stack<Type>& other);
	Stack<Type>& operator=(const Stack<Type>& other);
	~Stack();

	size_t getSize();
	bool empty() const;
	void add(const Type& element);
	void remove();
	Type& top();
	const Type& top() const;
};

template<class Type>
void Stack<Type>::copy(const Stack<Type>& other)
{
	this->elements = new Type[other.capacity];
	for (size_t i = 0; i < other.size; i++)
		this->elements[i] = other.elements[i];
	this->size = other.size;
	this->capacity = other.capacity;
}

template<class Type>
void Stack<Type>::erase()
{
	delete[] this->elements;
}

template<class Type>
void Stack<Type>::resize()
{
	this->capacity *= 2;
	Type* biggerStack = new Type[this->capacity];
	for (size_t i = 0; i < this->size; i++)
		biggerStack[i] = this->elements[i];
	this->erase();
	this->elements = biggerStack;
}

template<class Type>
Stack<Type>::Stack(const Stack<Type>& other)
{
	this->copy(other);
}

template<class Type>
Stack<Type>& Stack<Type>::operator=(const Stack<Type>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

template<class Type>
Stack<Type>::~Stack()
{
	this->erase();
}

template<class Type>
size_t Stack<Type>::getSize()
{
	return this->size;
}

template<class Type>
bool Stack<Type>::empty() const
{
	return this->size == 0;
}

template<class Type>
void Stack<Type>::add(const Type& element)
{
	if (this->size == this->capacity)
		this->resize();

	this->elements[this->size++] = element;
}

template<class Type>
void Stack<Type>::remove()
{
	if (!this->empty())
	    this->size--;
}

template<class Type>
Type& Stack<Type>::top()
{
	assert(!this->empty());
	return this->elements[this->size - 1];
}

template<class Type>
const Type& Stack<Type>::top() const
{
	assert(!this->empty());
	return this->elements[this->size - 1];
}
