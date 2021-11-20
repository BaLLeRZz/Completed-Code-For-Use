#pragma once
#include<iostream>

template<class Type>
struct ListBox
{
	Type data{};
	ListBox* ptr{};
	ListBox(const Type& data) : data(data) {};
};

template<class Type>
class Deck
{
private:
	ListBox<Type>* first{};
	ListBox<Type>* last{};
	size_t size{};
	void erase();
	void copy(const Deck<Type>& other);
public:
	Deck() = default;
	Deck(const Deck<Type>& other);
	Deck<Type>& operator=(const Deck<Type>& other);
	~Deck();

	void addBack(const Type& element);
	void addFront(const Type& element);
	void removeBack();
	void removeFront();
	void print() const;
};

template<class Type>
void Deck<Type>::erase()
{
	while (this->first)
	{
		ListBox<Type>* temp = this->first;
		this->first = this->first->ptr;
		delete temp;
	}
}

template<class Type>
void Deck<Type>::copy(const Deck<Type>& other)
{
	if (!other.first)
		return;

	this->size = other.size;
	this->first = new ListBox<Type>(other.first->data);
	this->last = this->first;
	ListBox<Type>* current = other.first;
	while (current)
	{
		this->last = current;
		this->last->ptr = current;
		current = current->ptr;
	}
}

template<class Type>
Deck<Type>::Deck(const Deck<Type>& other)
{
	this->copy(other);
}

template<class Type>
Deck<Type>& Deck<Type>::operator=(const Deck<Type>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy();
	}
	return *this;
}

template<class Type>
Deck<Type>::~Deck()
{
	this->erase();
}

template<class Type>
void Deck<Type>::addBack(const Type& element)
{
	this->size++;
	if (!this->last)
	{
		this->first = this->last = new ListBox<Type>(element);
		return;
	}

	ListBox<Type>* newElement = new ListBox<Type>(element);
	this->last->ptr = newElement;
	this->last = newElement;
}

template<class Type>
void Deck<Type>::addFront(const Type& element)
{
	this->size++;
	if (!this->last)
	{
		this->first = this->last = new ListBox<Type>(element);
		return;
	}

	ListBox<Type>* newElement = new ListBox<Type>(element);
	newElement->ptr = this->first;
	this->first = newElement;
}

template<class Type>
void Deck<Type>::removeBack()
{
	if (this->size == 0)
		return;

	ListBox<Type>* current = this->first;
	while (current->ptr != this->last)
		current = current->ptr;
	current->ptr = nullptr;
	delete this->last;
	this->last = current;
}

template<class Type>
void Deck<Type>::removeFront()
{
	if (this->size == 0)
		return;

	ListBox<Type>* temp = this->first;
	this->first = this->first->ptr;
	delete temp;
}

template<class Type>
void Deck<Type>::print() const
{
	if (this->size == 0)
		return;

	ListBox<Type>* current = this->first;
	while (current)
	{
		std::cout << current->data << " ";
		current = current->ptr;
	}
}
