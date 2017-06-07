#pragma once
#include "IndexedContainer.h"
#include "Deque.h"
template <class T>
class InsertableContainer :public virtual IndexedContainer<T>
{
public:

	virtual bool insertAt(int index, const T& value) = 0;
	virtual bool removeAt(int index) = 0;
	virtual ~InsertableContainer() = 0 {}
};

