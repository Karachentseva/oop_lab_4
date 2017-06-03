#pragma once
#include <string>
using namespace std;

template <typename T>
class Fibonacci
{
private:
	T first;
	T second;
	int _size;
public:
	class const_iterator : public iterator<bidirectional_iterator_tag, T>
	{
	private:
		int index;
		T current;
		T next;
	public:
		void operator--()
		{
			T tmp = current;
			current = next - current;
			next = tmp;
			index--;
		}
		void operator++()
		{
			T tmp = current;
			current = next;
			next = tmp + next;
			index++;
		}
		void operator+=(int ind)
		{
			for (int i = index + 1; i < index + ind; i++)
			{
				T tmp = current;
				current = next;
				next = tmp + next;
			}
			index = index + ind;
		}
		void operator-=(int ind)
		{
			for (int i = index; i < index + ind; i++)
			{
				T tmp = current;
				current = next - current;
				next = tmp;
			}
			index = index - ind;
		}
		const_iterator operator+(int ind)
		{
			const_iterator it(index, first, second);
			it += ind;
			return it;
		}
		const_iterator operator-(int ind)
		{
			const_iterator it(index, first, second);
			it -= ind;
			return it;
		}
		T* operator ->()
		{
			return &operator*();
		}
		T operator *()
		{
			return first;
		}
		bool operator>(const_iterator &other)
		{
			return index > other.index;
		}
		bool operator<(const_iterator &other)
		{
			return index < other.index;
		}
		bool operator>=(const_iterator &other)
		{
			return index >= other.index;
		}
		bool operator<=(const_iterator &other)
		{
			return index <= other.index;
		}

		bool operator==(const_iterator &other)
		{
			return index == other.index;
		}
		bool operator!=(const_iterator &other)
		{
			return index != other.index;
		}
	};

	Fibonacci(int _size);
	/*Fibonacci(int _size, T const& first, T const& second);
	T at(int i) const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	void resize(int s);
	int size() const;*/
	Fibonacci(int siz, T const& fir, T const& sec)
	{
		_size = siz;
		first = fir;
		second = sec;
	}


	T at(int i) const
	{
		if (index == 0)
			return first;
		if (index == 1)
			return second;
		if (i >= size())
			break;
		return at(index - 2) + at(index - 1);
	}

	template<class T>
	const_iterator cbegin() const
	{
		return const_iterator(1, first, second);
	}

	template<class T>
	const_iterator  cend() const
	{
		return const_iterator(_size, first, second);
	}

	template<class T>
	int size() const
	{
		return _size;
	}

	template<class T>
	void resize(int s)
	{
		_size = s;
	}

};

template<>
Fibonacci<string>::Fibonacci(int _size)
{
	first = "a";
	second = "b";
}

template<class T>
Fibonacci<T>::Fibonacci(int _size)
{
	first = 0;
	second = 1;
}
