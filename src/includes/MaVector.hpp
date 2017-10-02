#pragma once

#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <RandomAccessIterator.hpp>

/*
 * @startuml
 * class MaVector<T: class, Allocator = std::allocator<T>: class>{
 * 	+MaVector()
 * 	+MaVector(n: size_t, val: const T&)
 * 	+MaVector(it1: InputIterator, it2: InputIterator)
 * 	+MaVector(rhs: const MaVector<T>&)
 * 	+MaVector(rhs: const MaVector<T>&&)
 * 	+MaVector(il: std::initializer_list<T>)
 * 	+~MaVector()
 * 	+operator=(rhs: const MaVector<T>&): MaVector<T>&
 * 	+operator=(rhs: const MaVector<T>&&): MaVector<T>&
 * 	+operator=(il: std::initializer_list<T>): MaVector<T>&
 *
 *	-maxSize: size_t
 *	-currSize: size_t
 *	-elems: T*
 * }
 * @enduml
 * */

template<class T>
class MaVector
{
public:
	//Aliases
	using value_type = T;
	using allocator_type = std::allocator<T>;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using iterator = RandomAccessIterator<value_type>;
	using const_iterator = const iterator;
//	using reverser_iterator = ;
//	using const_reverser_iterator = const reverser_iterator;

	MaVector();
	MaVector(size_t n, const T& val);
	MaVector(std::initializer_list<T> il);

	//Iterators
	RandomAccessIterator<T> begin();
	const RandomAccessIterator<T> cbegin();
	RandomAccessIterator<T> end();
	const RandomAccessIterator<T> cend();

	//Modifiers
	void push_back(const T& e);
	void push_back(T&& e);
	void pop_back();
	void resize(const size_t n, value_type val = value_type());
	void assign(const RandomAccessIterator<T> first, const RandomAccessIterator<T> last);
	void assign(const size_t n, const value_type& val);
	void assign(std::initializer_list<T> il);
	void clear();
	RandomAccessIterator<T> insert(RandomAccessIterator<T> itPos, const value_type& val);
	RandomAccessIterator<T> insert(RandomAccessIterator<T> itPos, const size_t n, const value_type& val);
	RandomAccessIterator<T> insert(RandomAccessIterator<T> itPos, const RandomAccessIterator<T> first, const RandomAccessIterator<T> last);
	RandomAccessIterator<T> insert(RandomAccessIterator<T> itPos, value_type&& val);
	RandomAccessIterator<T> insert(RandomAccessIterator<T> itPos, std::initializer_list<T> il);
	RandomAccessIterator<T> erase(const RandomAccessIterator<T> it);
	RandomAccessIterator<T> erase(const RandomAccessIterator<T> first, const RandomAccessIterator<T> last);


	//Capacity
	size_t size() const { return currSize; }
	size_t max_size() const { return maxSize; }
	size_t capacity() const { return maxSize; }
	bool empty() const{ return currSize == 0;}


	//Element Access
	reference operator[](const unsigned pos){ return elems[pos]; }
	const_reference operator[](const unsigned pos) const { return elems[pos]; }
	reference at(const unsigned pos){ if(pos >= currSize) throw std::out_of_range("Index "
			"Out of Range"); return elems[pos]; }
	const_reference at(const unsigned pos) const{ if(pos >= currSize) throw std::out_of_range("Index "
				"Out of Range"); return elems[pos]; }
	reference front(){ return elems[0]; }
	const_reference front() const{ return elems[0]; }
	reference back(){ return elems[currSize - 1]; }
	const_reference back() const{ return elems[currSize - 1]; }
	pointer data(){ return elems; }
	const_pointer data() const{ return elems; }


private:
	size_t maxSize;
	size_t currSize;
	T* elems;
	allocator_type mAllocator;
};

template<typename T>
MaVector<T>::MaVector(): maxSize(20), currSize(0), elems(mAllocator.allocate(maxSize))
{}

template<typename T>
MaVector<T>::MaVector(size_t n, const T& val): maxSize(n*2), currSize(n), elems(mAllocator.allocate(maxSize))
{
	for(auto i = 0u; i < n; ++i)
		mAllocator.construct(&elems[i], val);
}

template<typename T>
MaVector<T>::MaVector(std::initializer_list<T> il): maxSize((il.size()!=0) ? il.size()*2 : 20),
	currSize(il.size()), elems(mAllocator.allocate(maxSize))
{
	T* crawler = elems;
	for(auto it = il.begin(); it != il.end(); ++it)
		mAllocator.construct(crawler++, *it);
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::begin()
{
	return RandomAccessIterator<T>(&elems[0]);
}

template<typename T>
const RandomAccessIterator<T> MaVector<T>::cbegin()
{
	return RandomAccessIterator<T>(&elems[0]);
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::end()
{
	return RandomAccessIterator<T>(&elems[currSize]);
}

template<typename T>
const RandomAccessIterator<T> MaVector<T>::cend()
{
	return RandomAccessIterator<T>(&elems[currSize]);
}

template<typename T>
void MaVector<T>::resize(const size_t n, value_type val)
{
	if(n > maxSize)
	{
		//reallocate new chunk of memory -> maxSize * 2
		//copy all current elem to new memory location
		//destroy then de alloc current memory chunk
		//fill in new elem to satisfy currSize == n
		//currSize = n
		do
		{
			maxSize *= 2;
		}while(n > maxSize);

		T* temp = mAllocator.allocate(maxSize);
		for(auto i = 0u; i < currSize; ++i)
		{
			mAllocator.construct(&temp[i], elems[i]);
			mAllocator.destroy(&elems[i]);
		}
		mAllocator.deallocate(elems, currSize);
		elems = temp;
		do
		{
			push_back(val);
		}while(currSize < n);
	}
	else if(n == currSize)
	{
		return;
	}
	else if(n > currSize)
	{
		//starting at last pos until currSize==n
		//construct val
		//currSize = n
		do
		{
			mAllocator.construct(&elems[currSize++], val);
//		}while(++currSize < n);
		}while(currSize < n);
	}
	else
	{
		//starting last pos-1 until currSize ==n
		//destroy elem at pos-1
		//currSize = n
		do
		{
//			--currSize;
			mAllocator.destroy(&elems[--currSize]);
		}while(currSize > n);
	}
}

template<typename T>
void MaVector<T>::push_back(const T& e)
{
	if(currSize < maxSize)
	{
		mAllocator.construct(&elems[currSize++], e);
//		currSize++;
	}
	else
	{
		//save in temporary var*, reallocate new chunk of memory -> maxSize * 2
		//copy construct all current elem to new memory location
		//construct e
		//currSize ++;
		//destroy then de alloc current memory chunk
		//reassign pointer private member to return pointer when using alloc
		maxSize *= 2;
		T* temp = mAllocator.allocate(maxSize);
		for(auto i = 0u; i < currSize; ++i)
		{
			mAllocator.construct(&temp[i], elems[i]);
			mAllocator.destroy(&elems[i]);
		}
		mAllocator.deallocate(elems, currSize);
		mAllocator.construct(&temp[currSize++], e);
//		currSize++;
		elems = temp;
	}
}

template<typename T>
void MaVector<T>::push_back(T&& e)
{
	if(currSize < maxSize)
	{
		mAllocator.construct(&elems[currSize++], std::forward<T>(e));
//		currSize++;
	}
	else
	{
		//save in temporary var*, reallocate new chunk of memory -> maxSize * 2
		//copy construct all current elem to new memory location
		//construct e
		//currSize ++;
		//destroy then de alloc current memory chunk
		//reassign pointer private member to return pointer when using alloc
		maxSize *= 2;
		T* temp = mAllocator.allocate(maxSize);
		for(auto i = 0u; i < currSize; ++i)
		{
			mAllocator.construct(&temp[i], elems[i]);
			mAllocator.destroy(&elems[i]);
		}
		mAllocator.deallocate(elems, currSize);
		mAllocator.construct(&temp[currSize++], std::forward<T>(e));
//		currSize++;
		elems = temp;
	}
}

template<typename T>
void MaVector<T>::pop_back()
{
	if(currSize > 0)
	{
		mAllocator.destroy(&elems[currSize--]);
//		--currSize;
	}
}

template<typename T>
void MaVector<T>::assign(const RandomAccessIterator<T> first, const RandomAccessIterator<T> last)
{
	unsigned totalElem = last - first;
	unsigned availableSpace = maxSize - currSize;
	if(availableSpace < totalElem)
	{
		//new approach
		do
		{
			maxSize *= 2;
			availableSpace = maxSize - currSize;
		}while(totalElem > availableSpace);

		T* temp = mAllocator.allocate(maxSize);
		for(auto i = 0u; i < currSize; ++i)
		{
			mAllocator.construct(&temp[i], elems[i]);
			mAllocator.destroy(&elems[i]);
		}
		mAllocator.deallocate(elems, currSize);
		elems = temp;
		for(auto it = first; it != last; ++it)
		{
			push_back(*it);
		}

		//destroy then realloc previous
		//get maxSize that will satisfy maxSize > totalElem
		//construct first-last in new allocated space
//		for(auto i = 0u; i < currSize; ++i)
//		{
//			mAllocator.destroy(&elems[i]);
//		}
//
//		mAllocator.deallocate(elems, currSize);
//		do
//		{
//			maxSize *= 2;
//		}while(totalElem > maxSize);
//		elems = mAllocator.allocate(maxSize);
//		for(auto i = 0u; i < totalElem; ++i)
//		{
//			mAllocator.construct(&elems[i], *(first+i));
//		}
//		currSize = totalElem;
	}
	else
	{
		//new approach
		for(auto it = first; it != last; ++it)
		{
			push_back(*it);
		}

//		unsigned assignedElems = 0;
//		for(auto i = 0u; i < currSize; ++i)
//		{
//			while(assignedElems < totalElem)
//			{
//				elems[i] = *(first+0);
//				++assignedElems;
//			}
//		}
//		while(assignedElems < totalElem)
//		{
//			mAllocator.construct(&elems[assignedElems], *(first+assignedElems));
//			++assignedElems;
//			++currSize;
//		}
	}
}

template<typename T>
void MaVector<T>::assign(const size_t n, const value_type& val)
{
	resize(currSize+n, val);
}

template<typename T>
void MaVector<T>::assign(std::initializer_list<T> il)
{
	for(auto it = il.begin(); it != il.end(); ++it)
	{
		resize(currSize+1, *it);
	}
}

template<typename T>
void MaVector<T>::clear()
{
	for(auto i = 0u; i < currSize; ++i)
	{
		mAllocator.destroy(&elems[i]);
	}
	currSize = 0;
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::insert(RandomAccessIterator<T> itPos, const value_type& val)
{
	T* temp;
	if(currSize >= maxSize)
	{
		maxSize *= 2;
	}
	temp = mAllocator.allocate(maxSize);
	T* temp2 = temp;
	auto it = begin();
	for(; it != itPos; ++it)
	{
		mAllocator.construct(temp2++, *it);
	}

	auto ret = RandomAccessIterator<T>(temp2);
	mAllocator.construct(temp2++, val);

	for(; it != end(); ++it)
	{
		mAllocator.construct(temp2++, *it);
	}
	for(auto i = 0u; i < currSize; ++i)
	{
		mAllocator.destroy(&elems[i]);
	}
	mAllocator.deallocate(elems, currSize++);
	elems = temp;
	return ret;
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::insert(RandomAccessIterator<T> itPos, const size_t n, const value_type& val)
{
	T* temp;
	unsigned avilableSpace = maxSize - currSize;
		unsigned neededSpace = n;
		while(avilableSpace < neededSpace)
		{
			maxSize *= 2;
			avilableSpace = maxSize - currSize;
		}
		temp = mAllocator.allocate(maxSize);
		T* temp2 = temp;
		auto it = begin();
		for(; it != itPos; ++it)
		{
			mAllocator.construct(temp2++, *it);
		}

		auto ret = RandomAccessIterator<T>(temp2);
		for(auto i = 0u; i < n; ++i)
		{
			mAllocator.construct(temp2++, val);
		}

		for(; it != end(); ++it)
		{
			mAllocator.construct(temp2++, *it);
		}
		for(auto i = 0u; i < currSize; ++i)
		{
			mAllocator.destroy(&elems[i]);
		}
		mAllocator.deallocate(elems, currSize);
		currSize += neededSpace;
		elems = temp;
		return ret;
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::insert(RandomAccessIterator<T> itPos, const RandomAccessIterator<T> first,
		const RandomAccessIterator<T> last)
{
	T* temp;
	unsigned avilableSpace = maxSize - currSize;
	unsigned neededSpace = last - first;
	while(avilableSpace < neededSpace)
	{
		maxSize *= 2;
		avilableSpace = maxSize - currSize;
	}
	temp = mAllocator.allocate(maxSize);
	T* temp2 = temp;
	auto it = begin();
	for(; it != itPos; ++it)
	{
		mAllocator.construct(temp2++, *it);
	}

	auto ret = RandomAccessIterator<T>(temp2);
	for(auto ilIt = first; ilIt != last; ++ilIt)
	{
		mAllocator.construct(temp2++, *ilIt);
	}

	for(; it != end(); ++it)
	{
		mAllocator.construct(temp2++, *it);
	}
	for(auto i = 0u; i < currSize; ++i)
	{
		mAllocator.destroy(&elems[i]);
	}
	mAllocator.deallocate(elems, currSize);
	currSize += neededSpace;
	elems = temp;
	return ret;
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::insert(RandomAccessIterator<T> itPos, value_type&& val)
{
	T* temp;
	if(currSize >= maxSize)
	{
		maxSize *= 2;
	}
	temp = mAllocator.allocate(maxSize);
	T* temp2 = temp;
	auto it = begin();
	for(; it != itPos; ++it)
	{
		mAllocator.construct(temp2++, *it);
	}

	auto ret = RandomAccessIterator<T>(temp2);
	mAllocator.construct(temp2++, std::forward<T>(val));

	for(; it != end(); ++it)
	{
		mAllocator.construct(temp2++, *it);
	}
	for(auto i = 0u; i < currSize; ++i)
	{
		mAllocator.destroy(&elems[i]);
	}
	mAllocator.deallocate(elems, currSize++);
	elems = temp;
	return ret;
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::insert(RandomAccessIterator<T> itPos, std::initializer_list<T> il)
{
	T* temp;
	unsigned avilableSpace = maxSize - currSize;
	unsigned neededSpace = il.size();
	while(avilableSpace < neededSpace)
	{
		maxSize *= 2;
		avilableSpace = maxSize - currSize;
	}
	temp = mAllocator.allocate(maxSize);
	T* temp2 = temp;
	auto it = begin();
	for(; it != itPos; ++it)
	{
		mAllocator.construct(temp2++, *it);
	}

	auto ret = RandomAccessIterator<T>(temp2);
	for(auto ilIt = il.begin(); ilIt != il.end(); ++ilIt)
	{
		mAllocator.construct(temp2++, *ilIt);
	}

	for(; it != end(); ++it)
	{
		mAllocator.construct(temp2++, *it);
	}
	for(auto i = 0u; i < currSize; ++i)
	{
		mAllocator.destroy(&elems[i]);
	}
	mAllocator.deallocate(elems, currSize);
	currSize += neededSpace;
	elems = temp;
	return ret;
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::erase(const RandomAccessIterator<T> it)
{
	if(it == (end()-1))
	{
		pop_back();
		return end();
	}
	else
	{
		T* temp = mAllocator.allocate(currSize - 1);
		unsigned newSize = 0;
		auto itr = begin();
		for(; itr != it; ++itr)
		{
			mAllocator.construct(&temp[newSize++], *itr);
		}
		++itr;
		mAllocator.construct(&temp[newSize++], *itr);
		++itr;
		auto ret = RandomAccessIterator<T>(&temp[newSize-1]);
		for(; itr != end(); ++itr)
		{
			mAllocator.construct(&temp[newSize++], *itr);
		}
		for(auto i = 0u; i < currSize; ++i)
		{
			mAllocator.destroy(&elems[i]);
		}
		mAllocator.deallocate(elems, currSize--);
		elems = temp;
		return ret;
	}
}

template<typename T>
RandomAccessIterator<T> MaVector<T>::erase(const RandomAccessIterator<T> first,
		const RandomAccessIterator<T> last)
{
	unsigned totalElemToErase = last - first;
	if(last == end())
	{
		for(auto i = 0u; i < totalElemToErase; ++i)
		{
			pop_back();
		}
		return end();
	}
	else
	{
		T* temp = mAllocator.allocate(currSize - totalElemToErase);
		unsigned newSize = 0;
		auto itr = begin();
		for(; itr != first; ++itr)
		{
			mAllocator.construct(&temp[newSize++], *itr);
		}
		itr = last;
		mAllocator.construct(&temp[newSize++], *itr);
		++itr;
		auto ret = RandomAccessIterator<T>(&temp[newSize-1]);
		for(; itr != end(); ++itr)
		{
			mAllocator.construct(&temp[newSize++], *itr);
		}
		for(auto i = 0u; i < currSize; ++i)
		{
			mAllocator.destroy(&elems[i]);
		}
		mAllocator.deallocate(elems, currSize);
		currSize = newSize;
		elems = temp;
		return ret;
	}
}










