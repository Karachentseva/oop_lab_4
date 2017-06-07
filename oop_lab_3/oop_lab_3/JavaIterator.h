#pragma once

template <class T>
class JavaIterator
{
public:
	typedef JavaIterator<T&> iterator;
	typedef T value_type;
	virtual T& next() = 0;
	virtual bool hasNext() const = 0;
	virtual JavaIterator *clone() const = 0;
	virtual ~JavaIterator() {}
};

