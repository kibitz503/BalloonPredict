#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "Node.h"

template <typename T>
class CircularQueue
{
public:
	CircularQueue ( );
	~CircularQueue ( );
	CircularQueue (const CircularQueue & copy);
	CircularQueue& operator=(const CircularQueue & rhs);

	bool isEmpty ( );

	//returns the first element
	T& First ( ) const;
	//returns the last element
	T& Last ( ) const;

	//pops a value off the queue
	void Pop ( );

	//adds a value onto the end of the queue
	void Append (T object);
	//adds a value onto the begining of the queue
	void Prepend (T object);

	//empties the queue
	void Purge ( );

	//returns the pointer to the head of the queue
	Node<T> * getHead ( );
	//returns the pointer to the tail of the queue
	Node<T> * getTail ( );
	//returns the number of elements in the queue
	int getCount ( );

private:
	//pointer to the head of the queue
	Node<T> * m_head;
	//pointer to the tail of the queue
	Node<T> * m_tail;
	//number of elements in the queue
	int m_count;
};

#endif


/************************************************************************
no arg c'tor of CircularQueue.
************************************************************************/
template <typename T>
CircularQueue<T>::CircularQueue ( ) : m_head(0), m_tail(0), m_count(0)
{ }


/************************************************************************
d'tor of CircularQueue.
************************************************************************/
template <typename T>
CircularQueue<T>::~CircularQueue ( )
{ 
	this->Purge();
}


/************************************************************************
copy c'tor of CircularQueue.
************************************************************************/
template <typename T>
CircularQueue<T>::CircularQueue (const CircularQueue<T> & copy)
{
	*this = copy;
}


/************************************************************************
Overloaded operator= of CircularQueue.
************************************************************************/
template <typename T>
CircularQueue<T>& CircularQueue<T>::operator= 
	(const CircularQueue<T> &rhs)
{
	Node<T> * temp_Node = rhs.m_head;

	if (this != &rhs)
	{
		m_head = 0;
		m_tail = 0;
		m_count = rhs.m_count;

		while (temp_Node != 0)
		{
			this->Append(temp_Node->getData());
			temp_Node = temp_Node->getNext();
		}
	}
	
	return *this;
}


/************************************************************************
isEmpty, checks to see if there are any elements in the list.
************************************************************************/
template <typename T>
bool CircularQueue<T>::isEmpty ( )
{
	bool isEmpty_return(false);

	if (m_head == 0)
	{
		isEmpty_return = true;
	}
	return isEmpty_return;
}


/************************************************************************
First, return a const reference to the first element in the list.
************************************************************************/
template <typename T>
T& CircularQueue<T>::First ( ) const
{
	if (m_head == 0)
		throw "no list.";
	else
		return m_head->getData();
}


/************************************************************************
Last, return a const reference to the last element in the list.
************************************************************************/
template <typename T>
T& CircularQueue<T>::Last ( ) const
{
	if (m_tail == 0)
		throw "no list.";
	else
		return m_tail->getData();
}


/************************************************************************
Pop, delete whatever is at the tail of the list.
************************************************************************/
template <typename T>
void CircularQueue<T>::Pop ( )
{
	Node<T> * temp_Node;

	if ( m_count == 1 )
	{
		delete m_head;
		m_head = 0;
		m_tail = 0;

		m_count--;
	}

	else
	{
		temp_Node = m_tail;
		m_tail = m_tail->getPrevious();
		delete temp_Node;

		m_count--;
	}
}

/************************************************************************
Append, add an item at the end of the list.
************************************************************************/
template <typename T>
void CircularQueue<T>::Append (T object)
{
	Node<T> * new_Node = new Node<T>(object);	//no delete yet..
	Node<T> * temp_Node;

	if (m_head == 0)
	{
		m_head = new_Node;
		m_tail = new_Node;
	}
	else if (m_head == m_tail)
	{
		m_tail = new_Node;
		m_tail->setPrevious(m_head);
		m_head->setNext(m_tail);
	}
	else
	{
		temp_Node = m_tail;
		m_tail = new_Node;
		m_tail->setPrevious(temp_Node);
		temp_Node->setNext(m_tail);
	}

	m_count++;
}


/************************************************************************
Prepend, add an item at the front of the list.
************************************************************************/
template <typename T>
void CircularQueue<T>::Prepend (T object)
{
	Node<T> * new_Node = new Node<T>(object);
	Node<T> * temp_Node;

	if (m_head == 0)
	{
		m_head = new_Node;
		m_tail = new_Node;
	}
	else if (m_head == m_tail)
	{
		m_head = new_Node;
		m_tail->setPrevious(m_head);
		m_head->setNext(m_tail);		
	}
	else
	{
		temp_Node = m_head;
		m_head = new_Node;
		m_head->setNext(temp_Node);
		temp_Node->setPrevious(m_head);
	}

	m_count++;
}

/************************************************************************
Purge, removes every element of the list.
************************************************************************/
template <typename T>
void CircularQueue<T>::Purge ( )
{
	Node<T> * trail;
	m_count = 0;

	do
	{
		if (m_head != m_tail)
		{
			trail = m_head;
			m_head = m_head->getNext();
			delete trail;
		}
		else
		{
			delete m_head;
			m_head = 0;
			m_tail = 0;
		}

	} while (m_head != 0);
}

/************************************************************************
getHead.
************************************************************************/
template <typename T>
Node<T> * CircularQueue<T>::getHead ( )
{
	return m_head;
}

/************************************************************************
getTail.
************************************************************************/
template <typename T>
Node<T> * CircularQueue<T>::getTail ( )
{
	return m_tail;
}

template <typename T>
int CircularQueue<T>::getCount ( )
{
	return m_count;
}