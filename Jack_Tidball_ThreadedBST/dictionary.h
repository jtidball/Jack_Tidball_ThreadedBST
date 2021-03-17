// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

#ifndef DICTIONARY_H
#define DICTIONARY_H

// The Dictionary abstract class.
template <typename Key, typename E>
class  Dictionary {
private:
	void operator =(const Dictionary&) {}
	Dictionary(const Dictionary&) {}

public:
	Dictionary() {}          // Default constructor
	virtual ~Dictionary() {} // Base destructor

	// Reinitialize dictionary
	virtual void clear() = 0;

	// Insert a record
	// k: The key for the record being inserted.
	// e: The record being inserted.
	virtual void insert(const Key& k, const E& e) = 0;

	// Return: A record matching "k" (NULL if none exists).
	// If multiple records match, return an arbitrary one.
	// k: The key of the record to find
	virtual std::string find(const Key& k) const = 0;

	// Return the number of records in the dictionary.
	virtual int size() = 0;
};
#endif