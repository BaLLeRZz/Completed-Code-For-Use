#pragma once
#include <iostream>

template<class T>
struct ListBox {
	T data;
	ListBox<T>* ptr;
	ListBox(T _data, ListBox<T>* _ptr = nullptr) : data(_data), ptr(_ptr) {};
};

template<class T>
class List {
private:
	ListBox<T>* start;
	ListBox<T>* end;
	size_t size;
	void erase();
	void copy(const List& other);
public:
	List();
	List(const List& other);
	List<T>& operator=(const List& other);
	~List();
	size_t getSize() const;
	void add(T element);
	void print() const;
};

template<class T>
void List<T>::erase()
{
	while (this->start)
	{
		ListBox<T>* temp = this->start;
		this->start = this->start->ptr;
		delete temp;
	}
}

template<class T>
void List<T>::copy(const List& other)
{
	if (!other.start)
		return;

	this->size = other.size;
	this->start = new ListBox<T>(other.start->data);
	this->end = this->start;
	ListBox<T>* current = other.start->ptr;
	while (current)
	{
		this->add(current->data);
		current = current->ptr;
	}

}

template<class T>
List<T>::List()
{
	this->size = 0;
	this->start = this->end = nullptr;
}

template<class T>
List<T>::List(const List& other)
{
	this->copy(other);
}

template<class T>
List<T>& List<T>::operator=(const List& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}


template<class T>
List<T>::~List()
{
	this->erase();
}

template<class T>
size_t List<T>::getSize() const
{
	return this->size;
}

template<class T>
void List<T>::add(T element)
{
	this->size++;
	if (!this->end)
		this->start = this->end = new ListBox<T>(element);

	else
	{
		ListBox<T>* newElement = new ListBox<T>(element);
		this->end->ptr = newElement;
		this->end = newElement;
	}
}

template<class T>
void List<T>::print() const
{
	ListBox<T>* current = this->start;
	while (current)
	{
		std::cout << current->data;
		std::cout << std::endl;
		current = current->ptr;
	}
}
