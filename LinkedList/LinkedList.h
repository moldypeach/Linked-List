/* Filename:        LinkedList.h
 * Last Modified:   14 March 2014
 * Author:          Todd Parker
 * Email:           todd.i.parker@maine.edu
 * Course:          CIS354 - Algorithms and Data Structures
 * 
 * LinkedList.h is a generic class that allows for the creation and maintenance
 * of a linked list. The only code added to LinkedList.h is the function remove(),
 * which was required for completion of the Module #4 Programming assignment. 
 * remove() first tests to ensure the Linked List has elements, then checks if the
 * passed element exists in the Linked List, and finally deletes all occurences of 
 * the passed element if it exists; and prints appropiate messages if it does not.
 * The remove() function reuses existing methods indexOf, to return index of item
 * if it exists, and removeAt() to remove an item by its index in Linked List.
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdexcept>
using namespace std;

template<typename T>
class Node
{
public:
  T element;  // Element contained in the node
  Node<T>* next; // Pointer to the next node

  Node() // No-arg constructor
  {
	next = NULL;
  }

  Node(T element) // Constructor
  {
	this->element = element;
	next = NULL;
  }
};

template<typename T>
class Iterator: public std::iterator<std::forward_iterator_tag, T>
{
public:
  Iterator(Node<T>* p)
  {
	current = p;
  };

  Iterator operator++() // Prefix ++
  {
	current = current->next;
	return *this;
  }

  Iterator operator++(int dummy) // Postfix ++
  {
	Iterator temp(current);
	current = current->next;
	return temp;
  }

  T& operator*()
  {
	return current->element;
  }

  bool operator==(const Iterator<T>& iterator)
  {
	return current == iterator.current;
  }

  bool operator!=(const Iterator<T>& iterator)
  {
	return current != iterator.current;
  }

private:
  Node<T>* current;
};

template<typename T>
class LinkedList
{
public:
  LinkedList();
  LinkedList(LinkedList<T>& list);
  virtual ~LinkedList();
  void addFirst(T element);
  void addLast(T element);
  T getFirst() const;
  T getLast() const;
  T removeFirst() throw (runtime_error);
  T removeLast();
  void add(T element);
  void add(int index, T element);
  void clear();
  bool contains(T element) const;
  T get(int index) const;
  int indexOf(T element) const;
  bool isEmpty() const;
  int lastIndexOf(T element) const;
  void remove(T element);
  int getSize() const;
  T removeAt(int index);
  T set(int index, T element);

  Iterator<T> begin() const
  {
	return Iterator<T>(head);
  };

  Iterator<T> end() const
  {
	return Iterator<T>(tail->next);
  };

private:
  Node<T>* head;
	Node<T>* tail;
  int size;
};

template<typename T>
LinkedList<T>::LinkedList()
{
  head = tail = NULL;
  size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>& list)
{
  head = tail = NULL;
  size = 0;

  Node<T>* current = list.head;
  while (current != NULL)
  {
	this->add(current->element);
	current = current->next;
  }
}

template<typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template<typename T>
void LinkedList<T>::addFirst(T element)
{
  Node<T>* newNode = new Node<T>(element);
  newNode->next = head;
  head = newNode;
  size++;

  if (tail == NULL)
	tail = head;
}

template<typename T>
void LinkedList<T>::addLast(T element)
{
  if (tail == NULL)
  {
	head = tail = new Node<T>(element);
  }
  else
  {
	tail->next = new Node<T>(element);
	tail = tail->next;
  }

  size++;
}

template<typename T>
T LinkedList<T>::getFirst() const
{
  if (size == 0)
	throw runtime_error("Index out of range");
  else
	return head->element;
}

template<typename T>
T LinkedList<T>::getLast() const
{
  if (size == 0)
	throw runtime_error("Index out of range");
  else
	return tail->element;
}

template<typename T>
T LinkedList<T>::removeFirst() throw (runtime_error)
{
  if (size == 0)
   throw runtime_error("No elements in the list");
  else
  {
	Node<T>* temp = head;
	head = head->next;
	if (head == NULL) tail = NULL;
	size--;
	T element = temp->element;
	delete temp;
	return element;
  }
}

template<typename T>
T LinkedList<T>::removeLast()
{
  if (size == 0)
	throw runtime_error("No elements in the list");
  else if (size == 1)
  {
	Node<T>* temp = head;
	head = tail = NULL;
	size = 0;
	T element = temp->element;
	delete temp;
	return element;
  }
  else
  {
	Node<T>* current = head;

	for (int i = 0; i < size - 2; i++)
	  current = current->next;

	Node<T>* temp = tail;
	tail = current;
	tail->next = NULL;
	size--;
	T element = temp->element;
	delete temp;
	return element;
  }
}

template<typename T>
void LinkedList<T>::add(T element)
{
  addLast(element);
}

template<typename T>
void LinkedList<T>::add(int index, T element)
{
  if (index == 0)
	addFirst(element);
  else if (index >= size)
	addLast(element);
  else
  {
	Node<T>* current = head;
	for (int i = 1; i < index; i++)
	  current = current->next;
	Node<T>* temp = current->next;
	current->next = new Node<T>(element);
	(current->next)->next = temp;
	size++;
  }
}

template<typename T>
void LinkedList<T>::clear()
{
  while (head != NULL)
  {
	Node<T>* temp = head;
	head = head->next;
	delete temp;
  }

  tail = NULL;
  size = 0;
}

template<typename T>
T LinkedList<T>::get(int index) const
{
  if (index < 0 || index > size - 1)
	throw runtime_error("Index out of range");

  Node<T>* current = head;
  for (int i = 0; i < index; i++)
	current = current->next;

  return current->element;
}

template<typename T>
int LinkedList<T>::indexOf(T element) const
{
  // Implement it in this exercise
  Node<T>* current = head;
  for (int i = 0; i < size; i++)
  {
	if (current->element == element)
	  return i;
	current = current->next;
  }

  return -1;
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
  return head == NULL;
}

template<typename T>
int LinkedList<T>::getSize() const
{
  return size;
}

template<typename T>
T LinkedList<T>::removeAt(int index)
{
  if (index < 0 || index >= size)
	throw runtime_error("Index out of range");
  else if (index == 0)
	return removeFirst();
  else if (index == size - 1)
	return removeLast();
  else
  {
	Node<T>* previous = head;

	for (int i = 1; i < index; i++)
	{
	  previous = previous->next;
	}

	Node<T>* current = previous->next;
	previous->next = current->next;
	size--;
	T element = current->element;
	delete current;
	return element;
  }
}

template<typename T>
void LinkedList<T>::remove(T element)
{
	// Make sure linked list is not empty
	if (size == 0)
	{
		throw runtime_error("List is empty");
	} // end if
	else if (indexOf(element) < 0)
		cout << "\n\t \"" << element << "\" was not found in list.\n" << endl;
	else
	{
		// Copy list size so deletes don't cause loop to skip elements
		int listSize = size;

		while (listSize > 0)
		{
			// Find index of element or return -1
			int elementIndex = indexOf(element);
			if (elementIndex > 0)
				// Delete found item by index
				removeAt(elementIndex);
			listSize--;
		}


	} // end else
} // end remove function

#endif
