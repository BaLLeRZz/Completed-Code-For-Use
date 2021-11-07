#pragma once
#include<iostream>
#include<cstring>
class String
{
private:
	char* name;
	void copy(const String&);
	void erase();
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
	~String();

	void clear();
	const char* getName() const;
	size_t getLength() const;
	size_t convertFromString();
	void remove(const size_t&);
	String& operator=(const char*);
	bool operator==(const String&) const;
	bool operator==(const char*) const;
	bool operator!=(const String&) const;
	bool operator!=(const char*) const;
	char& operator[](const size_t&);
	String& operator+=(const char&);

	friend std::ostream& operator<<(std::ostream& out, const String& str)
	{
		out << str.name;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, String& str)
	{
		String temp;
		char symbol = ' ';
		while (symbol != '\n')
		{
			symbol = in.get();
			temp += symbol;
		}
		temp[temp.getLength() - 1] = '\0';
		str = temp;
		return in;
	}
};