#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
	Node ( );
	~Node ( );

	Node (T data);
	Node (const Node &copy);
	Node& operator=(const Node &rhs);

	T& getData ( );
	void setData (T data);
	Node * getNext ( ) const;
	void setNext (Node * next);
	Node * getPrevious ( ) const;
	void setPrevious (Node * previous);

private:
	//holds the data of the node
	T m_data;
	//holds the pointer to the previous node
	Node * m_previous;
	//holds the pointer to the next node
	Node * m_next;
};


/************************************************************************
no arg c'tor of Node.
************************************************************************/
template <typename T>
Node<T>::Node ( ) : m_data(0), m_next(0), m_previous(0)
{ }


/************************************************************************
d'tor of Node.
************************************************************************/
template <typename T>
Node<T>::~Node ( )
{
	m_previous = 0;
	m_next = 0;
}


/************************************************************************
1 arg c'tor of Node.
************************************************************************/
template <typename T>
Node<T>::Node(T data) : m_data(data), m_next(0), m_previous(0)
{ }


/************************************************************************
copy c'tor of Node.
************************************************************************/
template <typename T>
Node<T>::Node(const Node<T> &copy) : m_data(copy.m_data), 
	m_next(copy.m_next), m_previous(copy.m_previous)
{
	//this can't be right.. shallow copy
}


/************************************************************************
Overloaded operator= of Node.
************************************************************************/
template <typename T>
Node<T>& Node<T>::operator=(const Node &rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_previous = rhs.m_previous;
	}
	return *this;
	//this can't be right.. shallow copy
}


/************************************************************************
Returns data member m_data.
************************************************************************/
template <typename T>
T& Node<T>::getData ( )
{
	return m_data;
}


/************************************************************************
Sets data member m_data equal to the parameter passed in.
************************************************************************/
template <typename T>
void Node<T>::setData (T data)
{
	m_data = data;
}


/************************************************************************
Returns data member m_next.
************************************************************************/
template <typename T>
Node<T> * Node<T>::getNext ( ) const
{
	return m_next;
}


/************************************************************************
Sets data member m_next equal to the parameter passed in.
************************************************************************/
template <typename T>
void Node<T>::setNext (Node * next)
{
	m_next = next;
}


/************************************************************************
Returns data member m_previous.
************************************************************************/
template <typename T>
Node<T> * Node<T>::getPrevious ( ) const
{
	return m_previous;
}


/************************************************************************
Returns data member m_previous.
************************************************************************/
template <typename T>
void Node<T>::setPrevious (Node * previous)
{
	m_previous = previous;
}


#endif