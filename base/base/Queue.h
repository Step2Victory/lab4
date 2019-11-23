#pragma once
template <typename T>
struct Node
{
	Node<T>* pNext = nullptr;
	T value;
};


template <typename T>
class Queue
{
	Node<T>* pFirst;
	Node<T>* pLast;
public:
	Queue()
	{
		pFirst = new Node<T>;
		pLast = new Node<T>;
		pFirst = nullptr;
		pLast = nullptr;
	}
	bool isEmpty();
	void push(T);
	T top();
	T pop();
	~Queue();
};

template<typename T>
bool Queue<T>::isEmpty()
{
	if (pFirst == nullptr && pLast == nullptr)
		return true;
	return false;
}

template<typename T>
void Queue<T>::push(T value)
{
	if (isEmpty())
	{
		Node<T>*p = new Node<T>;
		p->value = value;
		pFirst = pLast = p;
	}
	else
	{
		Node<T> *p = new Node<T>;
		p->value = value;
		pLast->pNext = p;
		pLast = p;
	}
}


template<typename T>
T Queue<T>::top()
{
	if (isEmpty())
		throw 1;
	return pFirst->value;
}

template<typename T>
T Queue<T>::pop()
{
	if (isEmpty())
		throw 1;
	else
	{
		T value = pFirst->value;
		Node<T> *p = pFirst->pNext;
		if (pFirst == pLast)
		{
			delete pFirst;
			pFirst = pLast = nullptr;
		}
		else
		{
			delete pFirst;
			pFirst = p;
		}
		return value;
	}
}


template<typename T>
Queue<T>::~Queue()
{
	while (pFirst != nullptr)
	{
		Node<T>* tmp = pFirst->pNext;
		delete pFirst;
		pFirst = tmp;
	}
}
