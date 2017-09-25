#pragma once

#include <iterator>

/*
 * @startuml
 * class RandomAccessIterator<T: typename> {
 * +RandomAccessIterator()
 * +RandomAccessIterator(elem: T*)
 * +RandomAccessIterator(const RandomAccessIterator<T>&)
 * +RandomAccessIterator& operator=(elem: T*)
 * +RandomAccessIterator& operator=(const RandomAccessIterator<T>&)
 * +~RandomAccessIterator()
 * +operator==(rhs: const RandomAccessIterator<T>&): bool
 * +operator!=(rhs: const RandomAccessIterator<T>&): bool
 * +operator*(): T&
 * +operator*() const: const T&
 * +operator->(): T*
 * +operator++(): RandomAccessIterator<T>&
 * +operator--(): RandomAccessIterator<T>&
 * +operator+(movement: const size_t): RandomAccessIterator<T>&
 * +operator-(movement: const size_t): RandomAccessIterator<T>&
 * +operator<(rhs: const RandomAccessIterator<T>&) const: bool
 * +operator>(rhs: const RandomAccessIterator<T>&) const: bool
 * +operator<=(rhs: const RandomAccessIterator<T>&) const: bool
 * +operator>=(rhs: const RandomAccessIterator<T>&) const: bool
 * +operator+=(movement: const size_t): RandomAccessIterator<T>&
 * +operator-=(movement: const size_t): RandomAccessIterator<T>&
 * +operator[](idx: const size_t): T&
 * +operator[](idx: const size_t) const: const T&
 * +getPtr(): T*
 * +getConstPtr() const: const T*
 * }
 * @enduml
 * */

template<typename T>
class RandomAccessIterator : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
{
public:
	RandomAccessIterator(T* elem = nullptr): mPtr(elem) {}
	RandomAccessIterator(const RandomAccessIterator<T>&) = default;
	RandomAccessIterator& operator=(T* elem){ mPtr = elem; return *this; }
	RandomAccessIterator& operator=(const RandomAccessIterator<T>&) = default;
	~RandomAccessIterator() = default;
	bool operator==(const RandomAccessIterator<T>& rhs) const;
	bool operator!=(const RandomAccessIterator<T>& rhs) const;
	T& operator*();
	const T& operator*() const;
	T* operator->();
	RandomAccessIterator<T>& operator++();
	RandomAccessIterator<T>& operator--();
	RandomAccessIterator<T> operator+(const size_t movement);
	RandomAccessIterator<T> operator-(const size_t movement);
	bool operator>(const RandomAccessIterator<T>& rhs) const;
	bool operator<(const RandomAccessIterator<T>& rhs) const;
	bool operator<=(const RandomAccessIterator<T>& rhs) const;
	bool operator>=(const RandomAccessIterator<T>& rhs) const;
	RandomAccessIterator<T>& operator+=(const size_t movement);
	RandomAccessIterator<T>& operator-=(const size_t movement);
//	T& operator[](const size_t idx);
//	const T& operator[](const size_t idx) const;
	T* getPtr();
	const T* getConstPtr() const;

private:
	T* mPtr;
};

template<typename T>
T* RandomAccessIterator<T>::getPtr()
{
	return mPtr;
}

template<typename T>
const T* RandomAccessIterator<T>::getConstPtr() const
{
	return mPtr;
}

template<typename T>
bool RandomAccessIterator<T>::operator==(const RandomAccessIterator<T>& rhs) const
{
	return (mPtr == rhs.getConstPtr());
}

template<typename T>
bool RandomAccessIterator<T>::operator!=(const RandomAccessIterator<T>& rhs) const
{
	return !(this == rhs);
}

template<typename T>
T& RandomAccessIterator<T>::operator*()
{
	return *mPtr;
}

template<typename T>
const T& RandomAccessIterator<T>::operator*() const
{
	return *mPtr;
}

template<typename T>
T* RandomAccessIterator<T>::operator->()
{
	return mPtr;
}

template<typename T>
RandomAccessIterator<T>& RandomAccessIterator<T>::operator++()
{
	++mPtr;
	return *this;
}

template<typename T>
RandomAccessIterator<T>& RandomAccessIterator<T>::operator--()
{
	--mPtr;
	return *this;
}

template<typename T>
RandomAccessIterator<T> RandomAccessIterator<T>::operator+(const size_t movement)
{
	return RandomAccessIterator<T>((this->mPtr + movement));
}

template<typename T>
RandomAccessIterator<T> RandomAccessIterator<T>::operator-(const size_t movement)
{
	return RandomAccessIterator<T>((this->mPtr - movement));
}

template<typename T>
bool RandomAccessIterator<T>::operator>(const RandomAccessIterator<T>& rhs) const
{
	return (mPtr > rhs.getConstPtr());
}

template<typename T>
bool RandomAccessIterator<T>::operator<(const RandomAccessIterator<T>& rhs) const
{
	return (mPtr < rhs.getConstPtr());
}

template<typename T>
bool RandomAccessIterator<T>::operator<=(const RandomAccessIterator<T>& rhs) const
{
	return (mPtr <= rhs.getConstPtr());
}

template<typename T>
bool RandomAccessIterator<T>::operator>=(const RandomAccessIterator<T>& rhs) const
{
	return (mPtr >= rhs.getConstPtr());
}

template<typename T>
RandomAccessIterator<T>& RandomAccessIterator<T>::operator+=(const size_t movement)
{
	mPtr += movement;
	return *this;
}

template<typename T>
RandomAccessIterator<T>& RandomAccessIterator<T>::operator-=(const size_t movement)
{
	mPtr -= movement;
	return *this;
}

//template<typename T>
//T& RandomAccessIterator<T>::operator[](const size_t idx)
//{
//
//}
//
//template<typename T>
//const T& RandomAccessIterator<T>::operator[](const size_t idx) const
//{
//
//}

