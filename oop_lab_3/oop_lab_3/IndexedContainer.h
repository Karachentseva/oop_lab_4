#pragma once
#include "Container.h"
template <class T>
class IndexedContainer :public virtual Container<T>
{
public:
	virtual T get(int index) const = 0;
	virtual T& get(int index) = 0;
	virtual bool set(int index, const T& value) = 0;
	T& operator [](int index);
	virtual ~IndexedContainer() = 0 {}
};

template<class T>
T& IndexedContainer<T>::operator[] (int index)
{
	return get(index);
}
