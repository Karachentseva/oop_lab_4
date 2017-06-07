#pragma once
#include <string>
#include "JavaIterator.h"
#include <string>
#include<string.h>
template <class T>
class Container;

template <class T>
std::ostream & operator<<(std::ostream & os, const Container<T> & ct)
{
	os << ct.toString();
	return os;
}

template <class T>
class Container
{
public:
	virtual int size() const = 0;
	virtual bool isEmpty() const;
	std::string toString() const;
	void Sort();
	template<class C>
	static void sort(C& c)// oop_lab_4
	{
		typename C::iterator it1 = typename C::iterator(c);//.createIterator();
		for (int i = 0; i < c.size() - 1; i++)
		{
			typename C::value_type& begin = it1.next();
			typename C::iterator it2 = typename C::iterator(c);
			int c = 0;
			while (c != i)
			{
				it2.next();
				c++;
			}
			while (it2.hasNext())
			{
				typename C::value_type& temp = it2.next();
				if (begin > temp)
				{
					swap(begin, temp);
				}
			}
		}
	}
	virtual JavaIterator<T&> *createIterator() = 0;
	virtual JavaIterator<const T&> *createConstIterator() const = 0;
	friend std::ostream& operator <<<T>(std::ostream & os, const Container& ct);
	bool operator ==(Container const& ct) const;
	virtual ~Container() = 0 {}
};
template <class T>	void sort(T& ct);
template <class T>
bool Container<T>::isEmpty() const
{
	return size() == 0;
}

template <class T>
std::string Container<T>::toString() const
{
	JavaIterator<const T&> *iter = createConstIterator();
	std::string result = "";
	while (iter->hasNext())
	{
		result.append(to_string(iter->next()));
		result.append(" ");
	}
	return result;
}
template <>
std::string Container<std::string>::toString() const
{
	JavaIterator<const std::string&> *iter = createConstIterator();
	std::string result = "";
	while (iter->hasNext())
	{
		result.append(iter->next());
		result.append(" ");
	}
	return result;
}
template<class T>
inline void Container<T>::Sort()
{
	JavaIterator<T&>* iter1 = createIterator();
	while (iter1->hasNext())
	{
		auto iter2 = iter1->clone();
		T& min = iter2->next();
		while (iter2->hasNext())
		{
			T& elem = iter2->next();
			if (elem < min)
			{
				swap(min, elem);
			}
		}
		iter1->next();
	}
}


template<class T>
bool Container<T>::operator ==(Container const& ct) const
{
	auto iter1 = createConstIterator();
	auto iter2 = ct.createConstIterator();
	while (iter1->hasNext() && iter2->hasNext())
	{
		if (iter1->next() != iter2->next())
			return false;
	}
	if (iter1->hasNext() != iter2->hasNext())
		return false;
	return true;
}

