#pragma once

template<typename T>
struct Node
{
	unsigned key;
	T data;
	Node<T>* next;
};

template<typename T>
struct DNode
{
	unsigned key;
	T data;
	DNode<T>* next;
	DNode<T>* prev;
};
