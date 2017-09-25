#pragma once

#include <iterator>

/*
 * @startuml
 * class BidirectionalIterator<T: typename> {
 * +BidirectionalIterator(elem: T*)
 * +BidirectionalIterator(const BidirectionalIterator&)
 * +BidirectionalIterator operator=(const BidirectionalIterator&)
 * +~BidirectionalIterator()
 * +operator==(rhs: const BidirectionalIterator<T>&): bool
 * +operator!=(rhs: const BidirectionalIterator<T>&): bool
 * +operator*(): T&
 * +operator*() const: const T&
 * +operator->(): T*
 * +operator->() const: const T*
 * +operator++(): BidirectionalIterator<T>&
 * +operator--(): BidirectionalIterator<T>&
 *
 * +getPtr(): T*
 * +getConstPtr() const: const T*
 * }
 * @enduml
 * */

template<typename T>
class BidirectionalIterator : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t, T*, T&>
{
public:
	BidirectionalIterator(T* elem = nullptr): mPtr(elem){}
	BidirectionalIterator(const BidirectionalIterator<T>&) = default;
	BidirectionalIterator& operator=(const BidirectionalIterator<T>&) = default;
	BidirectionalIterator& operator=(T* elem){ mPtr = elem; return *this; };
	~BidirectionalIterator() = default;

	bool operator==(const BidirectionalIterator<T>& rhs) const;
	bool operator!=(const BidirectionalIterator<T>& rhs) const;
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
	BidirectionalIterator<T>& operator++();
	BidirectionalIterator<T>& operator--();

	T* getPtr() const;
	const T* getConstPtr() const;

private:
	T* mPtr;
};

template<typename T>
bool BidirectionalIterator<T>::operator==(const BidirectionalIterator<T>& rhs) const
{
	return (mPtr == rhs.getPtr()) ? true : false;
}

template<typename T>
bool BidirectionalIterator<T>::operator!=(const BidirectionalIterator<T>& rhs) const
{
	return (*this == rhs) ? false : true;
}

template<typename T>
T& BidirectionalIterator<T>::operator*()
{
	return *mPtr;
}

template<typename T>
const T& BidirectionalIterator<T>::operator*() const
{
	return *mPtr;
}

template<typename T>
T* BidirectionalIterator<T>::operator->()
{
	return mPtr;
}

template<typename T>
const T* BidirectionalIterator<T>::operator->() const
{
	return mPtr;
}

template<typename T>
BidirectionalIterator<T>& BidirectionalIterator<T>::operator++()
{
	++mPtr;
	return *this;
}

template<typename T>
BidirectionalIterator<T>& BidirectionalIterator<T>::operator--()
{
	--mPtr;
	return *this;
}

template<typename T>
T* BidirectionalIterator<T>::getPtr() const
{
	return mPtr;
}

template<typename T>
const T* BidirectionalIterator<T>::getConstPtr() const
{
	return mPtr;
}
