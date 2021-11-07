#include "String.h"

void String::copy(const String& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy_s(this->name, strlen(other.name) + 1, other.name);
}

void String::erase()
{
	delete[] this->name;
}

String::String()
{
	this->name = new char[1];
	this->name[0] = '\0';
}

String::String(const char* _name)
{
	this->name = new char[strlen(_name) + 1];
	strcpy_s(this->name, strlen(_name) + 1, _name);
}

String::String(const String& other)
{
	this->copy(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

String::~String()
{
	this->erase();
}

void String::clear()
{
	char* temp = new char[1];
	temp[0] = '\0';
	this->erase();
	this->name = temp;
}

const char* String::getName() const
{
	return this->name;
}

size_t String::getLength() const
{
	return strlen(this->name);
}

size_t String::convertFromString()
{
	size_t count = 0;
	size_t size = this->getLength();
	for (size_t i = 0; i < size; i++)
		if (this->name[i] >= '0' && this->name[i] <= '9')
		{
			if (this->name[i + 1] < '0' || this->name[i + 1] > '9')
			{
				count++;
				break;
			}
			else
				count++;
		}

	size_t position = pow(10, count - 1);
	size_t sum = 0;
	for (size_t i = 0; i < size; i++)
		if (this->name[i] >= '0' && this->name[i] <= '9')
		{
			sum += position * (this->name[i] - 48);
			position /= 10;
		}

	return sum;
}

void String::remove(const size_t& index)
{
	if (index >= strlen(this->name))
		return;

	for (size_t i = index; i < strlen(this->name); i++)
		this->name[i] = this->name[i + 1];

	this->name[strlen(this->name)] = '\0';
}

String& String::operator=(const char* _name)
{
	this->erase();
	this->name = new char[strlen(_name) + 1];
	strcpy_s(this->name, strlen(_name) + 1, _name);
	return *this;
}

bool String::operator==(const String& other) const
{
	if (this == &other)
		return true;

	if (strlen(this->name) != strlen(other.name))
		return false;

	for (size_t i = 0; i < strlen(this->name); i++)
		if (this->name[i] != other.name[i])
			return false;

	return true;
}

bool String::operator==(const char* _name) const
{
	if (strlen(this->name) != strlen(_name))
		return false;

	for (size_t i = 0; i < strlen(this->name); i++)
		if (this->name[i] != _name[i])
			return false;

	return true;
}

bool String::operator!=(const String& other) const
{
	if (this == &other)
		return false;

	if (strlen(this->name) != strlen(other.name))
		return true;

	for (size_t i = 0; i < strlen(this->name); i++)
		if (this->name[i] != other.name[i])
			return true;

	return false;
}

bool String::operator!=(const char* _name) const
{
	if (strlen(this->name) != strlen(_name))
		return true;

	for (size_t i = 0; i < strlen(this->name); i++)
		if (this->name[i] != _name[i])
			return true;

	return false;
}

char& String::operator[](const size_t& index)
{
	if (index >= strlen(this->name))
		return this->name[this->getLength() - 1];

	return this->name[index];
}

String& String::operator+=(const char& element)
{
	char* temp = new char[strlen(this->name) + 2];
	for (size_t i = 0; i < strlen(this->name); i++)
		temp[i] = this->name[i];

	temp[strlen(this->name) + 1] = '\0';
	this->erase();
	this->name = temp;
	this->name[strlen(this->name) - 1] = element;
	this->name[strlen(this->name)] = '\0';
	return *this;
}