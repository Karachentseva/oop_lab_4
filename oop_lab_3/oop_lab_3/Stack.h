#pragma once
#include "PushPopContainer.h"

template <class T>
class Stack : public virtual PushPopContainer<T>
{
private:
	template <class S> struct Node;
	Node<T> *first;
	int _size;
public:
	Stack();
	Stack(const Stack<T>& st);
	Stack<T>& operator=(const Stack<T>& st);
	int size() const override;

	bool isEmpty() const override;
	bool push(const T& value) override;
	T pop() override;
	T peek() const override;
	T& peek() override;

	//итератор
	template <class S>
	class StackIterator : public JavaIterator<S&>
	{
	private:
		friend class Stack<S>;
		Node<S>* current;

	public:
		StackIterator(Node<S>* cur)
		{
			current = &(*(cur));
		}
		StackIterator(Stack<S> &s): StackIterator(s.first)
		{
		}
		StackIterator(StackIterator const& copy) {
			current = &(*(copy.current));
		}

		JavaIterator* clone() const override{
			return new StackIterator(*this);
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
	class StackConstIterator : public JavaIterator<S>
	{
	private:
		friend class Stack<S>;
		Node* current;
	public:
		StackConstIterator(Node* cur)
		{
			current = cur;
		}

		StackConstIterator(StackConstIterator const& copy) {
			current = &(*(copy.current));
		}

		virtual JavaIterator *clone() const {
			return new StackConstIterator(*this);
		}

		bool hasNext() const override {
			return current != nullptr;
		}
		const S& next() override {
			S& tmp = current->value;
			if (current != nullptr)
				current = current->next;
			return tmp;
		}
	};


	friend class StackIterator<T>;
	friend class StackConstIterator<const T, Node<T>>;
	JavaIterator<T&> *createIterator() override;
	JavaIterator<const T&> *createConstIterator() const override;
	typedef StackIterator<T> iterator;
	typedef T value_type;
	virtual ~Stack();
};

template <class T>
template <class S>
struct Stack<T>::Node {
	S value;
	Node *next;
	Node(const S& value) : value(value), next(nullptr)
	{

	}
};

template<class T>
JavaIterator<T&>* Stack<T>::createIterator()
{
	return new StackIterator<T>(this->first);
}
template<class T>
JavaIterator<const T&>* Stack<T>::createConstIterator() const
{
	return new StackConstIterator<const T&, Node<T>>(this->first);
}


template <class T>
Stack<T>::Stack()
{
	_size = 0;
	first = nullptr;
}

template<class T>
Stack<T>::Stack(const Stack<T>& st)
{
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		push(iter->next());
	}
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st)
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
int Stack<T>::size() const
{
	return _size;
}


template <class T>
bool Stack<T>::isEmpty() const
{
	return first == nullptr;
}

template <class T>
bool Stack<T>::push(const T& value)
{
	try {
		if (isEmpty())
			first = new Node<T>(value);
		else
		{
			Node<T>* tmp = new Node<T>(value);
			tmp->next = first;
			first = tmp;
		}
		_size++;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template <class T>
T Stack<T>::pop()
{
	if (!isEmpty())
	{
		T result = first->value;
		Node<T>* tmp = first->next;
		delete first;
		first = tmp;
		_size--;
		return result;
	}
	throw "The Stack is empty!";
}


template <class T>
T Stack<T>::peek() const
{
	if (!isEmpty())
		return first->value;
	throw "The Stack is empty!";
}

template <class T>
T& Stack<T>::peek()
{
	if (!isEmpty())
		return first->value;
	throw "The Stack is empty!";
}

template <class T>
Stack<T>::~Stack()
{
	Node<T>* tmp = first;
	while (tmp != nullptr)
	{
		first = tmp->next;
		delete tmp;
		tmp = first;
	}
}

