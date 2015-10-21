
#include "string.h"
#include <iostream>
#include <cstring>
#include <cassert>

/*************************************************
<string.h

String class to account for most of the posibilities a string is required to do.

Esmeralda Salamone, esmes@aie.edu.au, 9/23/2015
Modified: Ben Mecklenburg, 7319bmecklenburg@gmail.com , 10/19/2015

All rights reserved.
***************************************************/
//default constructor, allocates memory for an empty string
stg::string::string(void)
{
	m_data = new char[m_size = 1]{ '\0' };
}

//deconstructor, deletes allocated memory that is still pointed to
stg::string::~string()
{
	if (m_data != nullptr)
	{
		delete[] m_data;
	}
}

//length function to return the size of the string
size_t stg::string::length() const
{
	if (m_data != nullptr)
	{
		return strlen(m_data);
	}
	else return 0;
}

//constructor to create a new string that's empty with a custom size
stg::string::string(size_t size)
{
	m_size = size;
	m_data = new char[m_size]{'\0'};
}

//constructor that turns an array into a string that allocates the amount of memory we pass in
stg::string::string(const char * a, size_t size)
{	
	if (size <= 0)
	{
		size = 1;
	}

	if (a != nullptr)
	{
		m_data = new char[strlen(a) + 1];
		strcpy_s(m_data, strlen(a) + 1, a);
		resize(size);
	}
}

//constructor that converts an array into a string
stg::string::string(const char * a)
{
	if (a != nullptr)
	{
		m_size = strlen(a) + 1;
		m_data = new char[m_size];
		strcpy_s(m_data, m_size, a);
	}
	else string();
}

//constructor that copies the string that's passed in
stg::string::string(const string & a) //: m_data(nullptr), m_size(0)
{
	//operator=(a);
	if (a.m_data != nullptr)
	{
		m_size = a.size();
		m_data = new char[m_size];
		strcpy_s(m_data, m_size, a.m_data);
	}
	else
	{
		m_data = new char[m_size = 1]{ '\0' };
	}
}

//move constructor to steal the data from the string passed in and set it to null
stg::string::string(string && a)
{
	//operator=(std::move(a));
	m_data = a.m_data;
	m_size = a.m_size;
	a.m_data = nullptr;
	a.m_size = 0;
}

//assignment operator overload to handle strings, copies the data passed in if it's valid
stg::string & stg::string::operator=(const string & a)
{
	if (a.m_data != nullptr)
	{
		m_size = a.size();
		resize(m_size);
		strcpy_s(m_data, m_size, a.m_data);
	}
	
	if (m_size == 0) m_size = 1;
	
	
	return *this;
}

//	Used http://www.cppsamples.com/common-tasks/rule-of-five.html as a reference
	//	Move assignment operator overload that deletes our old data, steals the mem address and size. 
		//Then sets the passed in string to a blank usable state.
			//  If the string passed in is not itself.
stg::string & stg::string::operator=(string && a)
{
	if (this != &a)
	{
		if (m_data != a.m_data)
		{
			delete[] m_data;
			m_data = a.m_data;
			m_size = a.m_size;
			a.m_data = new char[a.m_size = 1]{ '\0' };
		}
		else
		{
			*this = string();
		}
	}
	
	return *this;
}

// Assignment operator overload to handle arrays
stg::string & stg::string::operator=(const char * a)
{
	if (a == nullptr)
	{
		m_size = 1;
	}
	else 
	{
		m_size = strlen(a) + 1;
	}
	if (m_data != nullptr)
	{
		delete[] m_data;
	}
	m_data = new char[m_size];
	strcpy_s(m_data, m_size, a);
	return *this;
}

//Plus equals operator to add a string to the current string
stg::string & stg::string::operator+=(const string & a)
{
	size_t prevSize = m_size;
	m_size = prevSize + strlen(a.cstring()) + 1;
	resize(m_size);
	strcat_s(m_data, m_size, a.cstring());
	return *this;
}

//compound assignment operator to add an array to the current string
stg::string & stg::string::operator+=(const char * a)
{
	size_t prevSize = m_size;
	m_size = prevSize + strlen(a) + 1;
	resize(m_size);
	strcat_s(m_data, strlen(a) + 1, a);
	return *this;
}

//compound assignment operator to add a character to the current string
stg::string & stg::string::operator+=(char a)
{
	size_t prevSize = m_size;
	m_size = prevSize + 2;
	resize(m_size);
	m_data[m_size - 1] = '\0';
	strcat_s(m_data, m_size, &a);
	
	return *this;
}

//
char & stg::string::operator[](size_t index)
{
	return this->m_data[index];
}

const char & stg::string::operator[](size_t index) const
{
	return this->m_data[index];
}

//self-explanitory
size_t stg::string::size() const
{
	return m_size;
}

//resizes the string in m_data and sets the temp mem address to m_data, if m_size is valid
void stg::string::resize(size_t size)
{
	if (!size || size > 10000)
	{
		delete m_data;
		m_data = new char[m_size = 1]{ '\0' };
		return;
	}
	else
	{
		m_size = size;
	}

	char *newArr = new char[size] {'\0'};
	if (m_data != nullptr)
	{
		if (m_size <= 0)
		{
			m_size = 1;
		}
		strncpy_s(newArr, size, m_data, _TRUNCATE);
		delete[] m_data;
	}
	m_data = newArr;
}

void stg::string::clear()
{
	delete [] m_data;
	m_data = new char[m_size = 1]{ '\0' };
	//strcpy_s(m_data, 1, '\0');
}

bool stg::string::empty() const
{
	if (strlen(m_data) == 0)
		return true;
	else 
		return false;
}

const char * stg::string::cstring() const
{
	return m_data;
}

bool stg::operator<(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == -1)
		return true;
	else
		return false;
}

bool stg::operator<(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == -1)
		return true;
	else
		return false;
}

bool stg::operator<(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == -1)
		return true;
	else
		return false;
}

bool stg::operator<=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 0 || strcmp(a.cstring(), b.cstring()) == -1)
		return true;
	else
		return false;
}

bool stg::operator<=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 0 || strcmp(a.cstring(), b) == -1)
		return true;
	else
		return false;
}

bool stg::operator<=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 0 || strcmp(a, b.cstring()) == -1)
		return true;
	else
		return false;
}

bool stg::operator>(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 1) 
		return true;
	else
		return false;
}

bool stg::operator>(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 1)
		return true;
	else
		return false;
}

bool stg::operator>(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 1)
		return true;
	else
		return false;
}

bool stg::operator>=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 0 || strcmp(a.cstring(), b.cstring()) == 1)
		return true;
	else
		return false;
}

bool stg::operator>=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 0 || strcmp(a.cstring(), b) == 1)
		return true;
	else
		return false;
}

bool stg::operator>=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 0 || strcmp(a, b.cstring()) == 1) 
		return true;
	else
		return false;
}

bool stg::operator!=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) != 0)
		return true;
	else 
		return false;
}

bool stg::operator!=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) != 0)
		return true;
	else 
		return false;
}

bool stg::operator!=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) != 0)
		return true;
	else 
		return false;
}

bool stg::operator==(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 0)
		return true;
	else 
		return false;
}

bool stg::operator==(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 0)
		return true;
	else
		return false;
}

bool stg::operator==(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 0)
		return true;
	else 
		return false;
}

stg::string stg::operator+(const string & a, const string & b)
{
	size_t newSize = a.size() + b.size();
	char *newArr = new char[newSize];
	strcpy_s(newArr, a.size(), a.cstring());
	strcat_s(newArr, newSize, b.cstring());
	string newString = string(newArr);
	delete[] newArr;

	return newString;
}

stg::string stg::operator+(const string & a, const char * b)
{
	size_t newSize = a.size() + strlen(b);
	char *newArr = new char[newSize];
	strcpy_s(newArr, a.size(), a.cstring());
	strcat_s(newArr, newSize, b);
	string newString = string(newArr);
	delete[] newArr;
	return newString;
}

stg::string stg::operator+(const char * a, const string & b)
{
	size_t newSize = strlen(a) + b.size();
	char *newArr = new char[newSize];
	strcpy_s(newArr, strlen(a) + 1, a);
	strcat_s(newArr, newSize, b.cstring());
	string newString = string(newArr);
	delete[] newArr;
	return newString;
}

stg::string stg::operator+(const string & a, char b)
{
	size_t newSize = a.size() + 2;
	char *newArr = new char[newSize];
	strcpy_s(newArr, a.size(), a.cstring());
	strcat_s(newArr, newSize, &b);
	string newString = string(newArr);
	delete[] newArr;
	return newString;
}

stg::string stg::operator+(char a, const string & b)
{
	size_t newSize = 2 + b.size();
	char *newArr = new char[newSize];
	strcpy_s(newArr, 2, &a);
	strcat_s(newArr, newSize, b.cstring());
	string newString = string(newArr);
	delete[] newArr;
	return newString;
}

std::ostream & stg::operator<<(std::ostream & os, const string & p)
{
	return os << p.cstring();
}

//tung helped
std::istream & stg::operator>>(std::istream & is, string & p)
{
	char data[180];
	is >> data;
	p = data;
	return is;
}

const stg::string stg::literals::operator""_stg(const char * a, size_t len)
{
	return string(a, len + 1);
}
