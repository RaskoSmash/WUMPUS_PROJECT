#pragma once

/*************************************************
<string.h

Just a header for all the functions in String.cpp

Esmeralda Salamone, esmes@aie.edu.au, 9/23/2015
Modified: Ben Mecklenburg, 7319bmecklenburg@gmail.com , 10/19/2015

All rights reserved.
***************************************************/


// This header forward declares ostream and istream
// iostream should still be included in the source file
#include <iosfwd>

namespace stg
{
	class string
	{
	private:
		char *m_data;	// Pointer to a dynamically allocated char array
		size_t m_size;	// How much data can our array currently store?

	public:	
		string(void); // set m_data and m_size to meaningful defaults

		string(size_t size); // create an empty string with a given amount of memory.
		string(const char *a, size_t size);
						// duplicate data in character array, and set our size to size.
		
		~string(); //  delete dynamic memory if any is still in use (rule of 5).

		// Constructors, use strcpy
		string(const char *a);		// should duplicate the data of the character array
		string(const string &a);	// should duplicate the data of the other string (rule of 5).
		string(string &&a);			// should 'steal' the dynamic memory from the other string (rule of 5).

		// Assignment operators, use strcpy
		string &operator=(const string &a); // should duplicate the data of the other string (rule of 5).
		string &operator=(string &&a);		// should 'steal' the dynamic memory from the other string (rule of 5).
		string &operator=(const char *a);	// should duplicate the data of the character array

		// Concatenation assignment (resize and use strcat())
		string &operator+=(const string &a);
		string &operator+=(const char *a);
		string &operator+=(char a);

		// Array indexing
		char &operator[](size_t index);				// write access to an indexed character
		const char &operator[](size_t index) const; // read-only access to an indexed character

		size_t length() const;	// return the length of the string (strlen)
		size_t size() const;	// return the max number of chars we could hold (m_size-1, for term char)

		void resize(size_t size);	// create a new array of size, strcpy old data, then delete old data
		void clear();				// set the first character to '\0'
		bool empty() const;			// returns true if the first character is '\0'

		const char *cstring() const;	// constant access to m_data

	};

	// Relational operator overloads- use strcmp()
		// less-than is true if alphabetical-ascending
	bool operator<(const string &a, const string &b);
	bool operator<(const string &a, const char *b); 
	bool operator<(const char *a, const string &b);

	bool operator<=(const string &a, const string &b);
	bool operator<=(const string &a, const char *b);
	bool operator<=(const char *a, const string &b);
		// greater-than is true if alphabetical-descending
	bool operator>(const string &a, const string &b);
	bool operator>(const string &a, const char *b);
	bool operator>(const char *a, const string &b);

	bool operator>=(const string &a, const string &b);
	bool operator>=(const string &a, const char *b);
	bool operator>=(const char *a, const string &b);

	bool operator!=(const string &a, const string &b);
	bool operator!=(const string &a, const char *b);
	bool operator!=(const char *a, const string &b);

	bool operator==(const string &a, const string &b);
	bool operator==(const string &a, const char *b);
	bool operator==(const char *a, const string &b);

	// Concatenation operations- so many possible combinations.
		// should create a new string that is the concatenation of the two passed in.
		// Should support single characters also.
	string operator+(const string &a, const string &b);
	string operator+(const string &a, const char *b);
	string operator+(const char *a, const string &b);

	string operator+(const string &a, char b);
	string operator+(char a, const string &b);

	// Literal operator overload, use given char data to create a string
	// ie, "I AM A STRING"_sfw; should create a string /class/ literal!
	inline namespace literals {
		const string operator""_stg(const char *a, size_t len); }

	std::ostream &operator<<(std::ostream &os, const string& p); //output stream operator
	std::istream &operator>>(std::istream &is, string& p); //input stream operator

}

