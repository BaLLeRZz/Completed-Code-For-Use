#pragma once
#include<iostream>

template<class T>
struct ListBox
{
	T value{};
	ListBox<T>* next{};
	ListBox() = default;
	ListBox(const T& value, ListBox<T>* next = nullptr) : value(value), next(next) {};
};

template<class T>
class List
{
private:
	size_t size{};
	ListBox<T>* first{};
	ListBox<T>* last{};
	void erase();
	void copy(const List<T>& other);
public:
	List();
	List(const List<T>& other);
	List<T>& operator=(const List<T>& other);
	~List();

	size_t get_size() const;
	ListBox<T>* get_first() const;
	ListBox<T>* get_last() const;

	void push_back(const T& element);
	void pop_back();
	void push_front(const T& element);
	void pop_front();
	void push_at(size_t index, const T& element);
	void pop_at(size_t index);
	void print() const;

	List<T>& append(const List<T>& other);

	T& operator[](const size_t index);

	friend std::ostream& operator<<(std::ostream& out, const List<T>& list)
	{
		ListBox<T>* current = list.first;
		while (current)
		{
			out << current->value << " -> ";
			current = current->next;
		}

		out << std::endl;
		return out;
	}
};

template<class T>
inline void List<T>::erase()
{
	if (this->size == 0)
		return;

	while (this->first)
	{
		ListBox<T>* to_delete = this->first;
		this->first = this->first->next;
		delete to_delete;
		this->size--;
	}

	this->first = this->last = nullptr;
	this->size = 0;
}

template<class T>
inline void List<T>::copy(const List<T>& other)
{
	if (other.size == 0)
	{
		List<T>::List();
		return;
	}

	ListBox<T>* current = other.first;
	while (current)
	{
		this->push_back(current->value);
		current = current->next;
	}
}

template<class T>
inline List<T>::List()
{
	this->size = 0;
	this->first = this->last = nullptr;
}

template<class T>
inline List<T>::List(const List<T>& other)
{
	this->copy(other);
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}

	return *this;
}

template<class T>
inline List<T>::~List()
{
	this->erase();
}

template<class T>
inline size_t List<T>::get_size() const
{
	return this->size;
}

template<class T>
inline ListBox<T>* List<T>::get_first() const
{
	return this->first;
}

template<class T>
inline ListBox<T>* List<T>::get_last() const
{
	return this->last;
}

template<class T>
inline void List<T>::push_back(const T& element)
{
	this->size++;
	if (!this->first)
	{
		this->first = this->last = new ListBox<T>(element);
		return;
	}

	ListBox<T>* new_element = new ListBox<T>(element);
	this->last->next = new_element;
	this->last = new_element;
}

template<class T>
inline void List<T>::pop_back()
{
	if (this->size == 0)
		return;

	if (this->size == 1)
	{
		this->size--;
		delete this->first;
		this->first = this->last = nullptr;
		return;
	}
	ListBox<T>* current = this->first;
	while (current->next != this->last)
		current = current->next;

	this->last = current;
	delete current->next;
	current->next = nullptr;
	this->size--;
}

template<class T>
inline void List<T>::push_front(const T& element)
{
	this->size++;
	if (!this->first)
	{
		this->first = this->last = new ListBox<T>(element);
		return;
	}

	ListBox<T>* new_element = new ListBox<T>(element);
	new_element->next = this->first;
	this->first = new_element;
}

template<class T>
inline void List<T>::pop_front()
{
	if (this->size == 0)
		return;

	if (this->size == 1)
	{
		this->size--;
		delete this->first;
		this->first = this->last = nullptr;
		return;
	}

	ListBox<T>* to_delete = this->first;
	this->first = this->first->next;
	delete to_delete;
	this->size--;
}

template<class T>
inline void List<T>::push_at(size_t index, const T& element)
{
	if (index > this->size)
		return;

	if (index == this->size || this->size == 0)
	{
		this->push_back(element);
		return;
	}

	if (index == 0)
	{
		this->push_front(element);
		return;
	}

	this->size++;
	ListBox<T>* current = this->first;
	size_t count = 1;
	while (count < index)
	{
		current = current->next;
		count++;
	}

	ListBox<T>* new_element = new ListBox<T>(element);
	new_element->next = current->next;
	current->next = new_element;
	current = new_element;
}

template<class T>
inline void List<T>::pop_at(size_t index)
{
	if (this->size == 0)
		return;
	
	if (index >= this->size)
		return;

	if (index == this->size - 1)
	{
		this->pop_back();
		return;
	}

	if (index == 0)
	{
		this->pop_front();
		return;
	}

	ListBox<T>* current = this->first;
	size_t count = 1;
	while (count < index)
	{
		current = current->next;
		count++;
	}

	ListBox<T>* to_delete = current->next;
	current->next = current->next->next;
	delete to_delete;
	to_delete = nullptr;
	this->size--;
}

template<class T>
inline void List<T>::print() const
{
	ListBox<T>* current = this->first;
	while (current)
	{
		std::cout << current->value << " -> ";
		current = current->next;
	}

	std::cout << std::endl;
}

template<class T>
inline List<T>& List<T>::append(const List<T>& other)
{
	ListBox<T>* current = other.first;
	while (current)
	{
		this->push_back(current->value);
		current = current->next;
	}

	return *this;
}

template<class T>
inline T& List<T>::operator[](const size_t index)
{
	if (index >= this->size)
		return this->last->value; // might be corrected in the future

	ListBox<T>* current = this->first;
	size_t count{};
	while (count != index)
	{
		current = current->next;
		count++;
	}

	return current->value;
}
