#pragma once
#include <string>
using namespace std;

template <typename T>
class Fibonacci
{
private:
	T first, second;
	int _size;
public:
	class const_iterator : public iterator<bidirectional_iterator_tag, T>
	{
	private:
		int index;
		T current;
		T next;
	public:
		const_iterator operator--()
		{
			T tmp = current;
			current = next - current;
			next = tmp;
			index--;
		}
		const_iterator operator++()
		{
			T tmp = current;
			current = next;
			next = tmp + next;
			index++;
			return *this;
		}
		
		const_iterator operator+=(int ind)
		{
			this->index += index;
			/*for (int i = index + 1; i < index + ind; i++)
			{
				T tmp = current;
				current = next;
				next = tmp + next;
			}
			index = index + ind;*/
			return *this;
		}
		const_iterator operator-=(int ind)
		{
			this->index -= index;
			/*for (int i = index; i < index + ind; i++)
			{
				T tmp = current;
				current = next - current;
				next = tmp;
			}
			index = index - ind;*/
			return (*this);
		}
		const_iterator(int index, T  &current, T  &next)
		{
			index = this->index;
			current = this->current;
			next = this->next;
		}
		const_iterator operator+(int ind)
		{
			this->index += ind;
			return *this;
		}
		const_iterator operator- (int ind)
		{
			this->index -= ind;
			return *this;
		}
		T* operator ->()
		{
			return &operator*();
		}
		T operator *()
		{
			return current;
		}
		bool operator>(const const_iterator &other)
		{
			return index > other.index;
		}
		bool operator<(const const_iterator &other)
		{
			return index < other.index;
		}
		bool operator>=(const const_iterator &other)
		{
			return index >= other.index;
		}
		bool operator<=(const const_iterator &other)
		{
			return index <= other.index;
		}

		bool operator==(const_iterator &other)
		{
			return index == other.index;
		}
		bool operator!=(const_iterator &other)
		{
			return this->index != other.index;
		}
	};

Fibonacci(int _size);
Fibonacci(int siz, T const& fir, T const& sec)
	{
		_size = siz;
		first = fir;
		second = sec;
	}

	
	T at(int i)
	{
		{
			if (i <= _size && i > 0)
			{
				const_iterator it(i, first, second);
				return *it;
			}
			return first;
		}
		/*if (index == 0)
			return first;
		if (index == 1)
			return second;
		if (i >= size())
			break;
		return at(index - 2) + at(index - 1);*/
	}

	/*const_iterator cbegin() {
		return const_iterator<T>(*this);
	}
	const_iterator cend() {
		return const_iterator<T>(_size, *this);
	}*/
	
	const_iterator cbegin() 
	{
		return const_iterator(1, first, second);
	}

	const_iterator cend() 
	{
		return const_iterator(_size, first, second);
	}


	int size() 
	{
		return _size;
	}

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
//
//template<>
//Fibonacci<string>::Fibonacci(int _size) 
//{
//	first = "a";
//	second = "b";
//}
//
//template<class T>
//Fibonacci<T>::Fibonacci(int _size) 
//{
//	first = 0;
//	second = 1;
//}
//
//template<class T>
//Fibonacci<T>::Fibonacci(int siz, T const& fir, T const& sec)
//{
//	_size = siz;
//	first = fir;
//	second = sec;
//}
//
//template<class T>
//T Fibonacci<T>::at(int i) const
//{
//	if (index == 0)
//		return first;
//	if (index == 1)
//		return second;
//	if (i >= size())
//		break;
//	return at(index - 2) + at(index - 1);
//}
//
//template<class T>
// Fibonacci<T>::const_iterator  Fibonacci<T>::cbegin() const
//{
//	return  Fibonacci<T>::const_iterator(1, first, second);
//}
//
//template<class T>
// Fibonacci<T>::const_iterator  Fibonacci<T>::cend() const
//{
//	return Fibonacci<T>::const_iterator(_size, first, second);
//}
//
//template<class T>
//int Fibonacci<T>::size() const
//{
//	return _size;
//}
//
//template<class T>
//void Fibonacci<T>::resize(int s)
//{
//	_size = s;
//}
