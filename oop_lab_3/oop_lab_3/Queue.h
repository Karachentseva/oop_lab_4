#pragma once
#include "PushPopContainer.h"
template<class T>
class Queue : public virtual PushPopContainer<T>
{
private:

	template <class S> struct Node;
	Node<T> *first;
	Node<T> *last;
	int _size;
public:

	Queue();
	Queue(const Queue<T>& st);
	Queue<T>& operator=(const Queue<T>& st);
	int size() const override;
	bool isEmpty() const override;
	bool push(const T& value) override;
	T pop() override;
	T peek() const override;
	T& peek()  override;

	//итератор
	template <class S>
	class QueueIterator : public JavaIterator<S&>
	{
	private:
		friend class Queue<S>;
		Node<S>* current;

	public:
		QueueIterator(Node<S>* cur)
		{
			current = cur;
		}
		QueueIterator(Stack<S> &s) : QueueIterator(s.first)
		{
		}
		QueueIterator(QueueIterator const& copy) {
			current = &(*(copy.current));
		}

		 JavaIterator<T&>* clone() const override {
			return new QueueIterator(*this);
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
	class QueueConstIterator : public JavaIterator<S>
	{
	private:
		friend class Queue<S>;
		Node* current;
	public:
		QueueConstIterator(Node* cur)
		{
			current = cur;
		}
		QueueConstIterator(QueueConstIterator const& copy) {
			current = &(*(copy.current));
		}

		virtual JavaIterator *clone() const {
			return new QueueConstIterator(*this);
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


	friend class QueueIterator<T>;
	friend class QueueConstIterator<const T, Node<T>>;
	JavaIterator<T&> *createIterator() override;
	JavaIterator<const T&> *createConstIterator() const override;
	typedef QueueIterator<T> iterator;
	typedef T value_type;
	virtual ~Queue();
};

template <class T>
template <class S>
struct Queue<T>::Node {
	S value;
	Node *next;
	Node(const S& value) : value(value), next(nullptr)
	{ }
};

template<class T>
JavaIterator<T&>* Queue<T>::createIterator()
{
	return new QueueIterator<T>(this->first);
}
template<class T>
JavaIterator<const T&>* Queue<T>::createConstIterator() const
{
	return new QueueConstIterator<const T&, Node<T>>(this->first);
}

template <class T>
Queue<T>::Queue()
{
	_size = 0;
	first = last = nullptr;
}

template<class T>
Queue<T>::Queue(const Queue<T>& st)
{
	auto iter = st.createConstIterator();
	while (iter->hasNext())
	{
		push(iter->next());
	}
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& st)
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
int Queue<T>::size() const
{
	return _size;
}
template <class T>
bool Queue<T>::isEmpty() const
{
	return first == nullptr;
}

template <class T>
bool Queue<T>::push(const T& value)
{
	try {
		if (isEmpty())
			first = last = new Node<T>(value);
		else
		{
			last->next = new Node<T>(value);
			last = last->next;
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
T Queue<T>::pop()
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
	throw "The Queue is empty!";
}

template <class T>
T Queue<T>::peek() const
{
	if (!isEmpty())
		return first->value;
	throw "The Queue is empty!";
}

template <class T>
T& Queue<T>::peek()
{
	if (!isEmpty())
		return first->value;
	throw "The Queue is empty!";
}


template <class T>
Queue<T>::~Queue()
{
	Node<T>* tmp = first;
	while (tmp != nullptr)
	{
		first = tmp->next;
		delete tmp;
		tmp = first;
	}
}
