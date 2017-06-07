#pragma once
#include "Deque.h"
template <class T>
class LinkedDeque : public virtual Deque<T>
{
private:
	template<class S> struct Node;
	Node<T>* first, *last;
	int s;
public:
	LinkedDeque();
	LinkedDeque(const LinkedDeque<T>& st);
	LinkedDeque<T>& operator=(const LinkedDeque<T>& st);
	int size() const override;
	bool isEmpty() const override;
	
	bool pushFront(const T& value) override;
	bool pushBack(const T& value) override;
	T popFront() override;
	T popBack() override;
	T peekFront() const override;
	T peekBack() const override;
	T& peekFront() override;
	T& peekBack() override;

	//итератор
	template <class S>
	class DequeIterator : public JavaIterator<S&>
	{
	private:
		friend class LinkedDeque<S>;
		Node<S>* current;

	public:
		DequeIterator(Node<S>* cur)
		{
			current = cur;
		}
		DequeIterator(LinkedDeque<S>* s)
		{
			current = &(*(s.first));
		}
		DequeIterator(DequeIterator const& copy) {
			current = &(*(copy.current));
		}

		virtual JavaIterator* clone() const {
			return new DequeIterator(*this);
		}
		bool hasNext() const override {
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
	class DequeConstIterator : public JavaIterator<S>
	{
	private:
		friend class LinkedDeque<S>;
		Node* current;
	public:
		DequeConstIterator(Node* cur)
		{
			current = cur;
		}
		DequeConstIterator(DequeConstIterator const& copy) {
			current = &(*(copy.current));
		}

		virtual JavaIterator *clone() const {
			return new DequeConstIterator(*this);
		}

		bool hasNext()  const override {
			return current != nullptr;
		}
		const S& next() override {
			S& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};


	friend class DequeIterator<T>;
	friend class DequeConstIterator<const T, Node<T>>;
	JavaIterator<T&> *createIterator() override;
	JavaIterator<const T&> *createConstIterator() const override;
	typedef T value_type;
	typedef DequeIterator<T> iterator;
	virtual ~LinkedDeque();
};

template <class T>
template<class S>
struct LinkedDeque<T>::Node {
	S value;
	Node *next;
	Node *prev;
	Node(const S& value) : value(value), next(nullptr), prev(nullptr)
	{
	}
};

template<class T>
JavaIterator<T&>* LinkedDeque<T>::createIterator()
{
	return new DequeIterator<T>(this->first);
}
template<class T>
JavaIterator<const T&>* LinkedDeque<T>::createConstIterator() const
{
	return new DequeConstIterator<const T&, Node<T>>(this->first);
}

template <class T>
LinkedDeque<T>::LinkedDeque() :s(0), first(nullptr), last(nullptr)
{
}

template<class T>
LinkedDeque<T>::LinkedDeque(const LinkedDeque<T>& st)
{
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		pushFront(iter->next());
	}
}

template<class T>
LinkedDeque<T>& LinkedDeque<T>::operator=(const LinkedDeque<T>& st)
{
	while (!isEmpty())
		popBack();
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		pushFront(iter->next());
	}
	return *this;
}

template <class T>
int LinkedDeque<T>::size() const
{
	return s;
}
template <class T>
bool LinkedDeque<T>::isEmpty() const
{
	return s == 0;
}


template <class T>
bool LinkedDeque<T>::pushFront(const T& value)
{
	if (isEmpty())
	{
		first = last = new Node<T>(value);
		s++;
		return true;
	}
	else
	{
		first->prev = new Node<T>(value);
		Node<T> *tmp = first;
		first = first->prev;
		first->next = tmp;
		s++;
		return true;
	}
	return false;
}

template <class T>
bool LinkedDeque<T>::pushBack(const T& value)
{
	if (isEmpty())
	{
		first = last = new Node<T>(value);
		s++;
		return true;
	}
	else
	{
		last->next = new Node<T>(value);
		Node<T> *tmp = last;
		last = last->next;
		last->prev = tmp;
		s++;
		return true;
	}
	return false;
}

template <class T>
T LinkedDeque<T>::popFront()
{
	T result = first->value;
	Node<T>* tmp = first->next;
	delete first;
	first = tmp;
	s--;
	return result;
}

template <class T>
T LinkedDeque<T>::popBack()
{
	T result = last->value;
	Node<T>* tmp = last->prev;
	delete last;
	last = tmp;
	s--;
	return result;
}

template <class T>
T LinkedDeque<T>::peekFront() const
{
	return first->value;
}

template <class T>
T LinkedDeque<T>::peekBack() const
{
	return last->value;
}

template <class T>
T& LinkedDeque<T>::peekFront()
{
	return first->value;
}

template <class T>
T& LinkedDeque<T>::peekBack()
{
	return last->value;
}


template <class T>
LinkedDeque<T>::~LinkedDeque()
{
	Node<T>* tmp = first;
	while (tmp != nullptr)
	{
		first = tmp->next;
		delete tmp;
		tmp = first;
	}
}


