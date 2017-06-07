#pragma once
#include "PushPopContainer.h"
#include "InsertableContainer.h"
#include <string>
#include<string.h>
template <class T>
class LinkedList : public virtual PushPopContainer<T>, public virtual InsertableContainer<T>
{
private:
	template<class S> struct Node;
	Node<T> *first, *last;
	int s;
public:
	LinkedList();
	LinkedList(const LinkedList<T>& st);
	LinkedList<T>& operator=(const LinkedList<T>& st);
	int size() const override;
	bool isEmpty() const override;
	bool push(const T& value) override;
	T pop() override;
	T peek() const override;
	T& peek() override;
	T get(int index) const override;
	T& get(int index) override;
	bool set(int index, const T& value) override;
	bool insertAt(int index, const T& value) override;
	bool removeAt(int index) override;

	//итератор
	template <class S>
	class ListIterator : public JavaIterator<S&>
	{
	private:
		friend class LinkedList<S>;
		Node<S>* current;

	public:
		ListIterator(Node<S>* cur)
		{
			current = cur;
		}
		ListIterator(ListIterator const& copy) {
			current = copy.current;
		}

		virtual JavaIterator*clone() const {
			return new ListIterator(*this);
		}
		bool hasNext()  const override {
			return current != nullptr;
		}
		S& next() override {
			S& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};

	//константный итератор
	template <class S, class Node>
	class ListConstIterator : public JavaIterator<S>
	{
	private:
		friend class LinkedList<S>;
		Node* current;
	public:
		ListConstIterator(Node* cur)
		{
			current = cur;
		}

		ListConstIterator(ListConstIterator const& copy) {
			current = copy.current;
		}

		virtual JavaIterator* clone() const {
			return new ListConstIterator(*this);
		}

		bool hasNext() const override {
			return current != nullptr;
		}
		const S& next() override {
			S tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};


	friend class ListIterator<T>;
	friend class ListConstIterator<const T, Node<T>>;
	JavaIterator<T&> *createIterator() override;
	JavaIterator<const T&> *createConstIterator() const override;
	typedef ListIterator<T> iterator;
	typedef T value_type;
	virtual ~LinkedList();
};

template <class T>
template<class S>
struct LinkedList<T>::Node {
	S value;
	Node *next;
	Node(const S& value) : value(value), next(nullptr)
	{

	}
};

template<class T>
JavaIterator<T&>* LinkedList<T>::createIterator()
{
	return new ListIterator<T>(this->last);
}
template<class T>
JavaIterator<const T&>* LinkedList<T>::createConstIterator() const
{
	return new ListConstIterator<const T&, Node<T>>(this->last);
}

template <class T>
LinkedList<T>::LinkedList()
{
	s = 0;
	first = last = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& st)
{
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		push(iter->next());
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& st)
{
	while (!isEmpty())
		pop();
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		push(iter->next());
	}
	return *this;
}

template <class T>
int LinkedList<T>::size() const
{
	return s;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
	return first == nullptr;
}


template <class T>
bool LinkedList<T>::push(const T& value)
{
	try {
		if (isEmpty())
			first = last = new Node<T>(value);
		else
		{
			Node<T>* tmp = new Node<T>(value);
			tmp->next = last;
			last = tmp;
		}
		s++;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template <class T>
T LinkedList<T>::pop()
{
	if (!isEmpty())
	{
		T result = last->value;
		Node<T>* tmp = last->next;
		delete last;
		last = tmp;
		s--;
		return result;
	}
	throw "The LinkedList is empty";
}

template <class T>
T LinkedList<T>::peek() const
{
	if (!isEmpty())
		return last->value;
	throw "The LinkedList is empty";
}

template <class T>
T& LinkedList<T>::peek()
{
	if (!isEmpty())
		return last->value;
	throw "The LinkedList is empty";
}

template <class T>
T LinkedList<T>::get(int index) const
{
	if (index < s)
	{
		index = s - index;
		Node<T>* tmp = last;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		return tmp->value;
	}
	throw "The LinkedList is empty";
}

template <class T>
T& LinkedList<T>::get(int index)
{
	if (index < s)
	{
		index = s - index;
		Node<T>* tmp = last;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		return tmp->value;
	}
	throw "The LinkedList is empty";
}

template <class T>
bool LinkedList<T>::set(int index, const T& value)
{
	if (index >= s)
		push(value);
	else
	{
		//index = s - index;
		Node<T>* tmp = last;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
			return 	true;
	}
	 throw "The LinkedList is empty!";
}

template <class T>
bool LinkedList<T>::insertAt(int index, const T& value)
{
	if (index < s)
	{
		index = s - index;
		Node<T>* tmp = last;
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		Node<T> *nd = new Node<T>(value);
		nd->next = tmp->next;
		tmp->next = nd;
		s++;
		return true;
	}
	return false;
}

template <class T>
bool LinkedList<T>::removeAt(int index)
{
	if (index < s)
	{
		index = s - index;
		Node<T>* tmp;
		if (index == 1)
		{
			tmp = last->next;
			delete last;
			last = tmp;
			s--;
			return true;
		}
		tmp = last;
		for (int i = 0; i < index - 1; i++)
		{
			tmp = tmp->next;
		}
		Node<T>* tmp2 = tmp->next;
		tmp->next = tmp2->next;
		delete tmp2;
		return true;
	}
	return false;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Node<T>* tmp = last;
	while (tmp != nullptr)
	{
		last = tmp->next;
		delete tmp;
		tmp = last;
	}
}
