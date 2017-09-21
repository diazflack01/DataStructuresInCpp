#pragma once

#include <iostream>
#include <Node.hpp>

/*
 * @startuml
 * class CircularSingleLinkedList<T: typename> {
 * 	+CircularSingleLinkedList()
 * 	+CircularSingleLinkedList(const CircularSingleLinkedList&) = delete
 * 	+CircularSingleLinkedList operator(const CircularSingleLinkedList&) = delete
 * 	~CircularSingleLinkedList()
 * 	+getHead(): Node<T>*
 * 	+getTail(): Node<T>*
 * 	+insertFront(key: unsigned, data: T): void
 * 	+printAllElem(): void
 * 	+getNodeWithKey(key: unsigned): Node<T>*
 * 	+insertNodeAfterKey(keyToInsertAfter: unsigned, key: unsigned, data: T): void
 * 	+deleteNodeAfterKey(key: unsigned): void
 * 	+clear(): void
 * 	-_head: Node<T>*
 * 	-_tail: Node<T>*
 * }
 * CircularSingleLinkedList *-- class Node
 * @enduml
 * */


template<typename T>
class CircularSingleLinkedList
{
public:
	CircularSingleLinkedList();
	CircularSingleLinkedList(const CircularSingleLinkedList&) = delete;
	CircularSingleLinkedList operator=(const CircularSingleLinkedList&) = delete;
	~CircularSingleLinkedList();

	Node<T>* getHead(){ return _head; }
	Node<T>* getTail(){ return _tail; }
	void insertFront(unsigned k, T d);
	Node<T>* getNodeWithKey(unsigned k);
	void insertNodeAfterKey(unsigned k, unsigned k2, T d);
	void deleteNodeAfterKey(unsigned k);
	void clear();
	void printAll();


private:
	Node<T>* _head;
	Node<T>* _tail;
};


template<typename T>
CircularSingleLinkedList<T>::CircularSingleLinkedList(): _head(nullptr), _tail(nullptr) {}

template<typename T>
CircularSingleLinkedList<T>::~CircularSingleLinkedList()
{
	if(nullptr != _head)
	{
		if(_head == _tail)
		{
			delete _head;
		}
		else
		{
			Node<T>* temp = _head;
			Node<T>* nodeToDel = temp;
			while(temp->next != _tail)
			{
				temp = temp->next;
				delete nodeToDel;
				nodeToDel = temp;
			}
			delete nodeToDel;
		}
	}
}

template<typename T>
void CircularSingleLinkedList<T>::insertFront(unsigned k, T d)
{
	Node<T>* newNode = new Node<T>;
	newNode->key = k;
	newNode->data = d;
	if(nullptr == _head)
	{
		newNode->next = newNode;
		_head = newNode;
		_tail = newNode;
	}
	else
	{
		newNode->next = _head;
		_tail->next = newNode;
		_head = newNode;
	}
}

template<typename T>
Node<T>* CircularSingleLinkedList<T>::getNodeWithKey(unsigned k)
{
	if(nullptr == _head)
	{
		return nullptr;
	}
	else if(_head == _tail)
	{
		return (_head->key == k) ? _head : nullptr;
	}
	else
	{
		Node<T>* temp = _head;
		while(temp != _tail)
		{
			if(temp->key == k)
			{
				return temp;
			}
			temp = temp->next;
		}
		return (temp->key == k) ? temp : nullptr;
	}
}

template<typename T>
void CircularSingleLinkedList<T>::insertNodeAfterKey(unsigned k, unsigned k2, T d)
{
	auto match = getNodeWithKey(k);
	if(nullptr != match)
	{
		Node<T>* newNode = new Node<T>;
		newNode->key = k2;
		newNode->data = d;
		if(_head == _tail)
		{
			newNode->next = _head;
			_head->next = newNode;
			_tail = newNode;
		}
		else if(_tail == match)
		{
			newNode->next = _head;
			match->next = newNode;
			_tail = newNode;
		}
		else
		{
			newNode->next = match->next;
			match->next = newNode;
		}
	}
}

template<typename T>
void CircularSingleLinkedList<T>::deleteNodeAfterKey(unsigned k)
{
	Node<T>* match = getNodeWithKey(k);
	if(nullptr == match || _head == _tail || _tail == match)
	{
		return;
	}
	else if(_tail == match->next)
	{
		delete _tail;
		_tail = match;
		_tail->next = _head;
	}
	else
	{
		Node<T>* nodeToDel = match->next;
		match->next = nodeToDel->next;
		delete nodeToDel;
	}
}

template<typename T>
void CircularSingleLinkedList<T>::clear()
{
	if(nullptr == _head)
	{
		return;
	}
	else if(_head == _tail)
	{
		delete _head;
		_head = nullptr;
		_tail = nullptr;
	}
	else
	{
		Node<T>* crawler = _head->next;
		Node<T>* nodeToDel = crawler;
		while(crawler != _head)
		{
			crawler = crawler->next;
			delete nodeToDel;
			nodeToDel = crawler;
		}
		delete nodeToDel;
		_head = nullptr;
		_tail = nullptr;
	}
}

template<typename T>
void CircularSingleLinkedList<T>::printAll()
{
	Node<T>* crawler = _head->next;
	std::cout << "Key:" << _head->key << "\tData:" << _head->data << std::endl;
	while(crawler != _head)
	{
		std::cout << "Key:" << crawler->key << "\tData:" << crawler->data << std::endl;
		crawler = crawler->next;
	}
}
