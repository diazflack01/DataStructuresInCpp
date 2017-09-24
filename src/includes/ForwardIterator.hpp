#pragma once

#include <iterator>

/*
 * @startuml
 * class ForwardIterator<T: typename> {
 * 	+ForwardIterator()
 *	+ForwardIterator(rhs: const ForwardIterator&)
 *	+ForwardIterator(elem: T*)
 *	+ForwardIterator& operator=(rhs: const ForwardIterator&)
 *	+~ForwardIterator()
 *	+operator==(rhs: ForwardIterator&) const: bool;
 *	+operator!=(rhs: ForwardIterator&) const: bool
 *	+operator*(): T&
 *	+operator*(): const T&
 *	+operator->(): T*
 *	+operator++(): ForwardIterator&
 *	+getPtr(): T*
 *	+getConstPtr(): const T*
 *	-mPtr: T*
 * }
 * @enduml
 * */

template<typename T>
class ForwardIterator : public std::iterator<std::input_iterator_tag, T, ptrdiff_t, T*, T&>
{
public:
	ForwardIterator(): mPtr(nullptr) {}
	ForwardIterator(const ForwardIterator<T>& rhs) = default;
	ForwardIterator(T* elem): mPtr(elem) {}
	ForwardIterator& operator=(const ForwardIterator<T>& rhs) { mPtr = rhs->mPtr; return this; }
	~ForwardIterator() = default;

	bool operator==(ForwardIterator<T>& rhs) const;
	bool operator!=(ForwardIterator<T>& rhs) const;
	T& operator*();
	const T& operator*() const;
	T* operator->(); // no test
	ForwardIterator<T>& operator++();

	T* getPtr(); // no test
	const T* getConstPtr() const; // no test

private:
	T* mPtr;
};

template<typename T>
bool ForwardIterator<T>::operator==(ForwardIterator<T>& rhs) const
{
	return (mPtr == rhs.getConstPtr());
}

template<typename T>
bool ForwardIterator<T>::operator!=(ForwardIterator<T>& rhs) const
{
	return (mPtr != rhs.getConstPtr());
}

template<typename T>
T& ForwardIterator<T>::operator*()
{
	return *mPtr;
}

template<typename T>
const T& ForwardIterator<T>::operator*() const
{
	return *mPtr;
}

template<typename T>
T* ForwardIterator<T>::operator->()
{
	return mPtr;
}

template<typename T>
ForwardIterator<T>& ForwardIterator<T>::operator++()
{
	++mPtr;
	return *this;
}

template<typename T>
T* ForwardIterator<T>::getPtr()
{
	return mPtr;
}

template<typename T>
const T* ForwardIterator<T>::getConstPtr() const
{
	return mPtr;
}
