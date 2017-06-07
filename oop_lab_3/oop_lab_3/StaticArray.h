#pragma once
#include "IndexedContainer.h"

template<class T>
class StaticArray : public virtual IndexedContainer<T>
{
private:
	T* arr;
	int si;
public:
	StaticArray(int sz);
	StaticArray(const StaticArray<T>& st);
	StaticArray<T>& operator=(const StaticArray<T>& st);
	int size() const override;
	bool isEmpty() const override;
	T get(int index) const override;
	T& get(int index) override;
	bool set(int index, const T& value) override;

	//итератор
	template <class S>
	class StaticArrayIterator : public JavaIterator<S&>
	{
	private:
		friend class StaticArray<S>;
		int current;
		int size;
		S* arr;
	public:
		StaticArrayIterator(S* _arr, int size) :
			arr(arr), size(size)
		{
			arr = _arr;
			current = 0;
		}
		StaticArrayIterator(StaticArrayIterator const& copy) {
			current = copy.current;
		}
		virtual JavaIterator<T&>* clone() const {
			return new StaticArrayIterator(*this);
		}
		bool hasNext() const override {
			return current < size;
		}
		S& next() override {
			S& tmp = arr[current];
			++current;
			return tmp;
		}
	};

	//константный итератор
	template <class S>
	class StaticArrayConstIterator : public JavaIterator<S&>
	{
	private:
		friend class StaticArray<S>;
		int current, size;
		S* arr;
	public:
		StaticArrayConstIterator(S* _arr, int size) :arr(arr), size(size)
		{
			arr = _arr;
			current = 0;
		}
		StaticArrayConstIterator(StaticArrayConstIterator const& copy) {
			current = copy.current;
		}
		virtual JavaIterator* clone() const {
			return new StaticArrayConstIterator(*this);
		}
		bool hasNext() const override
		{
			return current<size;
		}
		const S& next() override
		{
			S& tmp = arr[current];
			++current;
			return tmp;
		}
	};

	friend class StaticArrayIterator<T>;
	friend class StaticArrayConstIterator<const T>;
	JavaIterator<T&> *createIterator() override;
	JavaIterator<const T&> *createConstIterator() const override;
	typedef JavaIterator<T&> iterator;
	virtual ~StaticArray();
};

template<class T>
JavaIterator<T&>* StaticArray<T>::createIterator()
{
	return new StaticArrayIterator<T>(arr, si);
}
template<class T>
JavaIterator<const T&>* StaticArray<T>::createConstIterator() const
{
	return new StaticArrayConstIterator<const T>(arr, si);
}

template<class T>
StaticArray<T>::StaticArray(int sz)
{
	si = sz;
	arr = new T[si];
}

template<class T>
StaticArray<T>::StaticArray(const StaticArray<T>& st)
{
	arr = new T[st.size()];
	si = st.size();
	auto iter = st.createConstIterator();
	int ind = 0;
	while (iter->hasNext())
	{
		set(ind++, iter->next());
	}
}

template<class T>
StaticArray<T>& StaticArray<T>::operator=(const StaticArray<T>& st)
{
	delete[] arr;
	arr = new T[st.size()];
	si = st.size();
	auto iter = st.createConstIterator();
	int ind = 0;
	while (iter->hasNext())
	{
		set(ind++, iter->next());
	}
	return *this;
}

template<class T>
int StaticArray<T>::size() const
{
	return si;
}

template<class T>
bool StaticArray<T>::isEmpty() const
{
	return si == 0;
}


template<class T>
T StaticArray<T>::get(int index) const
{
	if (index<si)
		return arr[index];
	throw "The StaticArray is empty!";
}

template<class T>
T& StaticArray<T>::get(int index)
{
	if (index<si)
		return arr[index];
	throw "The Array is empty!";
}

template<class T>
bool StaticArray<T>::set(int index, const T&  value)
{
	if (index < si)
	{
		arr[index] = value;
		return true;
	}
	return false;
}

template<class T>
StaticArray<T>::~StaticArray()
{
	delete[] arr;
}

