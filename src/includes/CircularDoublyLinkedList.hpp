#pragma once

#include <string>
#include <Node.hpp>

/*
 * @startuml
 * class CircularDoublyLinkedList<T: typename>{
 * 	+CircularDoublyLinkedList();
 * 	+CircularDoublyLinkedList(const CircularDoublyLinkedList&) = delete;
 * 	+CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList&) = delete;
 *	+getHead(): DNode<T>*;
 *	+getTail(): DNode<T>*;
 *	+insertFront(key: unsigned, data: T);
 *	+insertBack(key: unsigned, data: T);
 *	+insertAfterKey(keyToSearch: unsigned, key: unsigned, data: T);
 *	+insertBeforeKey(keyToSearch: unsigned, key: unsigned, data: T);
 *	+getForwardListContentInStr(): std::string;
 *	+getBackwardListContentInStr(): std::string;
 *	+getNodeWithKey(key: unsigned): DNode<T>*;
 *	+getNodeWithKeyForwardSearch(key: unsigned): DNode<T>*; //not much gain
 *	+getNodeWithKeyBackwardSearch(key: unsigned): DNode<T>*; //not much gain
 *	+empty(): bool;
 *	+clear(): void;
 * 	-DNode<T>* _head;
 * 	-DNode<T>* _tail;
 * }
 * @enduml
 * * CircularDoublyLinkedList *-- "2" DNode
 * */

template<typename T>
class CircularDoublyLinkedList
{
public:
	CircularDoublyLinkedList(): _head(nullptr), _tail(nullptr) {}
	CircularDoublyLinkedList(const CircularDoublyLinkedList&) = delete;
	CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList&) = delete;

	DNode<T>* getHead(){ return _head; }
	DNode<T>* getTail(){ return _tail; }
	void insertFront(unsigned key, T data);
	void insertBack(unsigned key, T data);
	void insertAfterKey(unsigned keyToSearch, unsigned key, T data);
	void insertBeforeKey(unsigned keyToSearch, unsigned key, T data);
	std::string getForwardListContentInStr(); //no test
	std::string getBackwardListContentInStr(); //no test
	DNode<T>* getNodeWithKey(unsigned key);

	bool empty() const;


private:
	DNode<T>* _head;
	DNode<T>* _tail;
};

template<typename T>
void CircularDoublyLinkedList<T>::insertFront(unsigned key, T data)
{
	DNode<T>* newNode = new DNode<T>;
	newNode->key = key;
	newNode->data = data;
	if(empty())
	{
		newNode->next = newNode;
		newNode->prev = newNode;
		_head = newNode;
		_tail = newNode;
	}
	else
	{
		newNode->next = _head;
		newNode->prev = _tail;
		_head->prev = newNode;
		_tail->next = newNode;
		_head = newNode;
	}
}

template<typename T>
void CircularDoublyLinkedList<T>::insertBack(unsigned key, T data)
{
	DNode<T>* newNode = new DNode<T>;
	newNode->key = key;
	newNode->data = data;
	if(empty())
	{
		newNode->next = newNode;
		newNode->prev = newNode;
		_head = newNode;
		_tail = newNode;
	}
	else
	{
		newNode->next = _head;
		newNode->prev = _tail;
		_head->prev = newNode;
		_tail->next = newNode;
		_tail = newNode;
	}
}

template<typename T>
void CircularDoublyLinkedList<T>::insertAfterKey(unsigned keyToSearch, unsigned key, T data)
{
	auto match = getNodeWithKey(keyToSearch);
	if(nullptr != match)
	{
		if(_head == _tail || _tail == match)
		{
			insertBack(key, data);
		}
		else
		{
			DNode<T>* newNode = new DNode<T>;
			newNode->key = key;
			newNode->data = data;
			newNode->next = match->next;
			newNode->next->prev = newNode;
			newNode->prev = match;
			match->next = newNode;
		}
	}
}

template<typename T>
void CircularDoublyLinkedList<T>::insertBeforeKey(unsigned keyToSearch, unsigned key, T data)
{
	auto match = getNodeWithKey(keyToSearch);
	if(nullptr != match)
	{
		if(_head == _tail || _head == match)
		{
			insertFront(key, data);
		}
		else
		{
			DNode<T>* newNode = new DNode<T>;
			newNode->key = key;
			newNode->data = data;
			newNode->prev = match->prev;
			newNode->prev->next = newNode;
			match->prev = newNode;
			newNode->next = match;
		}
	}
}

template<typename T>
DNode<T>* CircularDoublyLinkedList<T>::getNodeWithKey(unsigned key)
{
	if(empty())
	{
		return nullptr;
	}
	else
	{
		DNode<T>* crawler = _head;
		do
		{
			if(crawler->key == key)
				return crawler;
			crawler = crawler->next;
		}while(crawler != _head);
		return nullptr;
	}
}

template<typename T>
bool CircularDoublyLinkedList<T>::empty() const
{
	return (nullptr == _head) ? true : false;
}

template<typename T>
std::string CircularDoublyLinkedList<T>::getForwardListContentInStr()
{
	std::string ret("");
	if(!empty())
	{
		DNode<T>* crawler = _head;
		do
		{
			ret.append(std::to_string(crawler->key) + ", " + std::to_string(crawler->data));
			ret.push_back('\n');
			crawler = crawler->next;
		}while(crawler != _head);
	}
	return ret;
}

template<typename T>
std::string CircularDoublyLinkedList<T>::getBackwardListContentInStr()
{
	std::string ret("");
	if(!empty())
	{
		DNode<T>* crawler = _tail;
		do
		{
			ret.append(std::to_string(crawler->key) + ", " + std::to_string(crawler->data));
			ret.push_back('\n');
			crawler = crawler->prev;
		}while(crawler != _tail);
	}
	return ret;
}
