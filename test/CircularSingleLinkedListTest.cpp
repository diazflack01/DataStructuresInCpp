#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <utility>
#include <CircularSingleLinkedList.hpp>
#include <Node.hpp>

namespace helper
{

template<typename T>
bool isCSLEqual(std::vector<std::pair<unsigned, T>> expected, Node<T>* head)
{
	decltype(head) crawler = head;
	for(auto it = expected.begin(); it != expected.end(); ++it)
	{
		if(it->first != crawler->key || it->second != crawler->data)
		{
			return false;
		}
		crawler = crawler->next;
		if(it+1 != expected.end() && crawler == head)
		{
			return false;
		}
	}
	return (crawler != head) ? false : true;
}

std::vector<std::pair<unsigned, int>> createExpectedMessage1()
{
	std::vector<std::pair<unsigned, int>> ret;
	for(auto i = 0u; i < 10; ++i)
	{
		ret.emplace_back(std::make_pair(i, i*2));
	}
	return ret;
}

}

TEST(TestCircularSingleLinkedList, getHead_ShouldReturnNullptrWhenEmpty)
{
	CircularSingleLinkedList<int> intCSL;
	ASSERT_EQ(nullptr, intCSL.getHead());
}

TEST(TestCircularSingleLinkedList, getHead_ShouldReturnFirstElemWhenNotEmpty)
{
	CircularSingleLinkedList<int> intCSL;
	intCSL.insertFront(1,2);
	intCSL.insertFront(3,2);
	ASSERT_EQ(3u, intCSL.getHead()->key);
	ASSERT_EQ(2, intCSL.getHead()->data);
}

TEST(TestCircularSingleLinkedList, getTail_ShouldReturnNullptrWhenEmpty)
{
	CircularSingleLinkedList<int> intCSL;
	ASSERT_EQ(nullptr, intCSL.getTail());
}

TEST(TestCircularSingleLinkedList, getTail_ShouldReturnLastElemWhenNotEmpty)
{
	CircularSingleLinkedList<int> intCSL;
	intCSL.insertFront(1,2);
	intCSL.insertFront(3,2);
	ASSERT_EQ(1u, intCSL.getTail()->key);
	ASSERT_EQ(2, intCSL.getTail()->data);
	intCSL.insertFront(5,2);
	ASSERT_EQ(1u, intCSL.getTail()->key);
	ASSERT_EQ(2, intCSL.getTail()->data);
}

TEST(TestCircularSingleLinkedList, getNodeWithKey_ShouldReturnNullptrWhenKeyDoesNotExist)
{
	CircularSingleLinkedList<int> intCSL;
	ASSERT_EQ(nullptr, intCSL.getNodeWithKey(1));
	intCSL.insertFront(1,2);
	ASSERT_EQ(nullptr, intCSL.getNodeWithKey(2));
}

TEST(TestCircularSingleLinkedList, getNodeWithKey_ShouldReturnCorrectNodeWhenKeyExist)
{
	CircularSingleLinkedList<int> intCSL;
	intCSL.insertFront(1,2);
	intCSL.insertFront(2,4);
	auto match = intCSL.getNodeWithKey(2);
	ASSERT_TRUE((nullptr != match));
	ASSERT_EQ(2u, match->key);
	ASSERT_EQ(4, match->data);
	match = intCSL.getNodeWithKey(1);
	ASSERT_TRUE((nullptr != match));
}

TEST(TestCircularSingleLinkedList, insertNodeAfterKey_ShouldNotInsertNodeIfKeyToSearchIsNotFound)
{
	std::vector<std::pair<unsigned, int>> EXPECTED = helper::createExpectedMessage1();
	CircularSingleLinkedList<int> intCSL;

	for(auto i = 9; i >= 0; --i)
	{
		intCSL.insertFront(i, i*2);
	}

	for(auto i = 10; i < 20; ++i)
	{
		intCSL.insertNodeAfterKey(i, 1, 1);
		ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
	}
}

TEST(TestCircularSingleLinkedList, insertNodeAfterKey_ShouldInsertNodeIfKeyToSearchIsFound)
{
	std::vector<std::pair<unsigned, int>> EXPECTED = helper::createExpectedMessage1();
	CircularSingleLinkedList<int> intCSL;

	for(auto i = 9; i >= 0; --i)
	{
		intCSL.insertFront(i, i*2);
	}

	for(auto i = 0u, k = 1u; i < 10; ++i, ++k)
	{
		intCSL.insertNodeAfterKey(i, i+20, ((i+2)*2));
		auto itToInsert = EXPECTED.begin()+(i+k);
		EXPECTED.emplace(itToInsert, std::make_pair(i+20, ((i+2)*2)));
		ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
	}
}

TEST(TestCircularSingleLinkedList, deleteNodeAfterKey_shouldNotDeleteIfSearchedKeyIsTail)
{
	std::vector<std::pair<unsigned, int>> EXPECTED = helper::createExpectedMessage1();
	CircularSingleLinkedList<int> intCSL;

	for(auto i = 9; i >= 0; --i)
	{
		intCSL.insertFront(i, i*2);
	}
	intCSL.deleteNodeAfterKey(9);
	ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
}

TEST(TestCircularSingleLinkedList, deleteNodeAfterKey_shouldDeleteNextElemWhenSearchedKeyIsHead)
{
	std::vector<std::pair<unsigned, int>> EXPECTED = helper::createExpectedMessage1();
	CircularSingleLinkedList<int> intCSL;

	for(auto i = 9; i >= 0; --i)
	{
		intCSL.insertFront(i, i*2);
	}
	intCSL.deleteNodeAfterKey(0);
	EXPECTED.erase(EXPECTED.begin()+1);
	ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
}

TEST(TestCircularSingleLinkedList, deleteNodeAfterKey_shouldDeleteNextElemWhenSearchedKeyIsBetweenHeadAndTail)
{
	std::vector<std::pair<unsigned, int>> EXPECTED = helper::createExpectedMessage1();
	CircularSingleLinkedList<int> intCSL;

	for(auto i = 9; i >= 0; --i)
	{
		intCSL.insertFront(i, i*2);
	}
	intCSL.deleteNodeAfterKey(8);
	EXPECTED.erase(EXPECTED.begin()+9);
	ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
	intCSL.deleteNodeAfterKey(4);
	EXPECTED.erase(EXPECTED.begin()+5);
	ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
	intCSL.deleteNodeAfterKey(1);
	EXPECTED.erase(EXPECTED.begin()+2);
	ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
	intCSL.deleteNodeAfterKey(1);
	EXPECTED.erase(EXPECTED.begin()+2);
	ASSERT_TRUE(helper::isCSLEqual(EXPECTED, intCSL.getHead()));
}
