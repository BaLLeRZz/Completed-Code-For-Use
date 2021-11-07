#pragma once
#include <iostream>

template<class T>
class Vector
{
private:
	T* vector;
	size_t size;
	size_t capacity;
	void erase();
	void copy(const Vector<T>&);
	void resize();
public:
	Vector();
	Vector(const Vector<T>&);
	Vector<T>& operator=(const Vector<T>&);
	~Vector();

	size_t getSize() const;
	void insert(const T&, const size_t&);
	void add(const T&);
	void remove(const size_t&);
	void clear();
	void print() const;
	void reverse();
	bool containsAnother(const Vector<T>&) const;
	T& operator[](const size_t&) const;
	bool operator!=(const char*) const;

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vector)
	{
		for (size_t i = 0; i < vector.size; i++)
			out << vector.vector[i] << std::endl << std::endl;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, const Vector<T>& vector)
	{
		for (size_t i = 0; i < vector.size; i++)
			in >> vector.vector[i];
		return in;
	}
};

template<class T>
void Vector<T>::erase()
{
	delete[] this->vector;
}

template<class T>
void Vector<T>::copy(const Vector<T>& other)
{
	this->size = other.size;
	this->capacity = other.capacity;
	this->vector = new T[this->capacity];
	for (size_t i = 0; i < this->size; i++)
		this->vector[i] = other.vector[i];
}

template<class T>
void Vector<T>::resize()
{
	this->capacity *= 2;

	T* biggerVector = new T[this->capacity];
	for (size_t i = 0; i < this->size; i++)
		biggerVector[i] = this->vector[i];

	delete[] this->vector;
	this->vector = biggerVector;
}

template<class T>
Vector<T>::Vector()
{
	this->size = 0;
	this->capacity = 10;
	this->vector = new T[this->capacity];
}

template<class T>
Vector<T>::Vector(const Vector<T>& other)
{
	this->copy(other);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	this->erase();
}

template<class T>
size_t Vector<T>::getSize() const
{
	return this->size;
}

template<class T>
void Vector<T>::insert(const T& element, const size_t& index)
{
	if (this->size >= this->capacity)
		this->resize();

	for (size_t i = this->size; i > index; i--)
		this->vector[i] = this->vector[i - 1];

	this->vector[index] = element;
	this->size++;
}

template<class T>
void Vector<T>::add(const T& element)
{
	if (this->size >= this->capacity)
		this->resize();

	this->vector[this->size++] = element;
}

template<class T>
void Vector<T>::remove(const size_t& index)
{
	if (index >= this->size)
		return;

	T* temp = new T[this->size - 1];
	for (size_t i = index; i < this->size; i++)
		this->vector[i] = this->vector[i + 1];

	for (size_t i = 0; i < this->size - 1; i++)
		temp[i] = this->vector[i];

	delete[] this->vector;
	this->vector = temp;
	this->size--;
}

template<class T>
void Vector<T>::clear()
{
	this->size = 0;
	this->capacity = 10;
	this->erase();
	this->vector = new T[capacity];
}

template<class T>
void Vector<T>::print() const
{
	for (size_t i = 0; i < this->size; ++i)
		std::cout << this->vector[i] << " ";
}

template<class T>
void Vector<T>::reverse()
{
	if (this->size == 0)
		return;

	T* temp = new T[this->size];
	size_t k = 0;
	for (int i = size - 1; i >= 0; i--)
		temp[k++] = this->vector[i];

	this->erase();
	this->vector = temp;
}

template<class T>
bool Vector<T>::containsAnother(const Vector<T>& other) const
{
	size_t sizeOther = other.getSize();
	bool flag;
	for (size_t i = 0; i < sizeOther; i++)
	{
		for (size_t j = 0; j < this->size; j++)
		{
			if (other[i] == this->vector[j])
			{
				flag = true;
				break;
			}
			else
				flag = false;
		}
		if (!flag)
			return false;
	}
	return true;
}

template<class T>
T& Vector<T>::operator[](const size_t& index) const
{
	if (index >= this->size)
		return this->vector[this->size - 1];

	return this->vector[index];
}

template<class T>
bool Vector<T>::operator!=(const char* name) const
{
	if (this->size != strlen(name))
		return true;

	for (size_t i = 0; i < this->size; i++)
		if (this->vector[i] == name[i])
			return false;
	return true;
}