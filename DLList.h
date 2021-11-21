#pragma once
#include<iostream>

template<class T>
struct ListBox
{
	T data{};
	ListBox* next{};
	ListBox* previous{};
	ListBox() = default;
	ListBox(const T& data) : data(data), next(nullptr), previous(nullptr) {};
};

template<class T>
class DLList
{
private:
	ListBox<T>* first{};
	ListBox<T>* last{};
	size_t size;
	void copy(const DLList<T>& other);
	void erase();
public:
	DLList() = default;
	DLList(const DLList<T>& other);
	DLList<T>& operator=(const DLList<T>& other);
	~DLList();

	void pushBack(const T& element);
	void popBack();
	void pushFront(const T& element);
	void popFront();

	friend std::ostream& operator<<(std::ostream& out, const DLList<T>& list)
	{
		ListBox<T>* current = list.first;
		while (current)
		{
			std::cout << current->data << " ";
			current = current->next;
		}
		return out;
	}

	template<class T>
	class Iterator
	{
	private:
		ListBox<T>* ptr;
	public:
		Iterator(ListBox<T>* ptr) : ptr(ptr) {};
		Iterator<T>& operator++() // ++i
		{
			this->ptr = this->ptr->next;
			return *this;
		}

		Iterator<T> operator++(int) // i++
		{
			Iterator<T> cpy = *this;
			this->ptr = this->ptr->next;
			return cpy;
		}

		const bool operator==(const Iterator<T>& other) const
		{
			return this->ptr == other.ptr;
		}

		const bool operator!=(const Iterator<T>& other) const
		{
			return !(*this == other);
		}

		T& operator*() // *i
		{
			return this->ptr->data;
		}
	};

	const Iterator<T>& begin() const
	{
		return Iterator<T>(this->first);
	}

	const Iterator<T> end() const
	{
		return Iterator<T>(nullptr);
	}
};

template<class T>
void DLList<T>::copy(const DLList<T>& other)
{
	if (!other.first)
		return;

	this->size = other.size;
	this->first = new ListBox<T>(other.first->data);
	ListBox<T>* current = new ListBox<T>(other.first);
	while (current)
	{
	    this->last = current;
	    this->last->next = current;
		current = current->next;
	}
}

template<class T>
void DLList<T>::erase()
{
	while (this->first)
	{
		ListBox<T>* temp = this->first;
		this->first = this->first->next;
		delete temp;
	}
}

template<class T>
DLList<T>::DLList(const DLList<T>& other)
{
	this->copy(other);
}

template<class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

template<class T>
DLList<T>::~DLList()
{
	this->erase();
}

template<class T>
void DLList<T>::pushBack(const T& element)
{
	this->size++;
	if (!this->first)
	{
		this->first = this->last = new ListBox<T>(element);
		return;
	}

	ListBox<T>* newElement = new ListBox<T>(element);
	newElement->previous = this->last;
	this->last->next = newElement;
	this->last = newElement;
}

template<class T>
void DLList<T>::popBack()
{
	if (this->size == 0)
		return;

	if (this->size == 1)
	{
		this->size--;
		delete this->last;
		this->last = this->first = nullptr;
		return;
	}

	this->size--;
	this->last->next = this->last;
	this->last = this->last->previous;
	delete this->last->next;
	this->last->next = nullptr;
}

template<class T>
void DLList<T>::pushFront(const T& element)
{
	this->size++;
	if (!this->first)
	{
		this->first = this->last = new ListBox<T>(element);
		return;
	}

	ListBox<T>* newElement = new ListBox<T>(element);
	newElement->next = this->first;
	this->first = newElement;
	ListBox<T>* current = this->first;
	while (current->next)
	{
		ListBox<T>* temp = current->next;
		if (!temp->next)
		{
			this->last->previous = current;
			this->last = temp;
			this->last->next = nullptr;
			return;
		}
		current = current->next;
	}
}

template<class T>
void DLList<T>::popFront()
{
	if (this->size == 0)
		return;
	
	this->size--;
	this->first->previous = this->first;
	this->first = this->first->next;
	delete this->first->previous;
	this->first->previous = nullptr;
}
