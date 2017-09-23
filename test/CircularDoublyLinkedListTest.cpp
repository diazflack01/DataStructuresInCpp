#include <gtest/gtest.h>

#include <vector>
#include <utility>
#include <CircularDoublyLinkedList.hpp>

namespace helper {

template<typename T>
bool isDLLEqual(std::vector<std::pair<unsigned, T>> expected, DNode<T>* head)
{
	if(head == nullptr)
		return false;

	decltype(head) crawler = head;
	for(auto it = expected.begin(); it != expected.end(); ++it)
	{
		if(it->first != crawler->key || it->second != crawler->data)
		{
			return false;
		}
		crawler = crawler->next;
		if(it+1 != expected.end() && crawler == head) // this will be true once all DLL elem is iterated and expected still has uncompared values
		{
			return false;
		}
	}
	return (crawler != head) ? false : true;
}

std::vector<std::pair<unsigned, int>> createExpectedMessageDLL()
{
	std::vector<std::pair<unsigned, int>> ret;
	for(auto i = 0u; i < 10; ++i)
	{
		ret.emplace_back(std::make_pair(i, i*2));
	}
	return ret;
}

}

TEST(TestCircularDoublyLinkedList, getHead_ShouldReturnNullptrWhenEmpty)
{
	CircularDoublyLinkedList<int> intCSL;
	ASSERT_EQ(nullptr, intCSL.getHead());
}

TEST(TestCircularDoublyLinkedList, getHead_ShouldReturnFirstElemWhenNotEmpty)
{
	CircularDoublyLinkedList<int> intCSL;
	intCSL.insertFront(1,2);
	intCSL.insertFront(3,2);
	ASSERT_EQ(3u, intCSL.getHead()->key);
	ASSERT_EQ(2, intCSL.getHead()->data);
}

TEST(TestCircularDoublyLinkedList, getTail_ShouldReturnNullptrWhenEmpty)
{
	CircularDoublyLinkedList<int> intCSL;
	ASSERT_EQ(nullptr, intCSL.getTail());
}

TEST(TestCircularDoublyLinkedList, getTail_ShouldReturnLastElemWhenNotEmpty)
{
	CircularDoublyLinkedList<int> intCSL;
	intCSL.insertFront(1,2);
	intCSL.insertFront(3,2);
	ASSERT_EQ(1u, intCSL.getTail()->key);
	ASSERT_EQ(2, intCSL.getTail()->data);
}

TEST(TestCircularDoublyLinkedList, empty_shouldReturnTrueWhenEmpty)
{
	CircularDoublyLinkedList<int> intCSL;
	ASSERT_TRUE(intCSL.empty());
}

TEST(TestCircularDoublyLinkedList, empty_shouldReturnFalseWhenNotEmpty)
{
	CircularDoublyLinkedList<int> intCSL;
	intCSL.insertFront(1,2);
	intCSL.insertFront(3,2);
	ASSERT_FALSE(intCSL.empty());
}

TEST(TestCircularDoublyLinkedList, insertFront_shouldSetHeadAndTailEqualWhenListIsEmpty)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertFront(1, 2);
	ASSERT_TRUE(nullptr != intDLL.getHead());
	ASSERT_TRUE(nullptr != intDLL.getTail());
	ASSERT_TRUE(helper::isDLLEqual(std::vector<std::pair<unsigned, int>>{std::make_pair(1,2)}, intDLL.getHead()));
}

TEST(TestCircularDoublyLinkedList, insertFront_shouldInsertInCorrectOrder)
{
	CircularDoublyLinkedList<int> intDLL;
	for(auto i = 9; i >= 0; --i)
	{
		intDLL.insertFront(i, i*2);
	}

	ASSERT_TRUE(helper::isDLLEqual(helper::createExpectedMessageDLL(), intDLL.getHead()));
}

TEST(TestCircularDoublyLinkedList, insertBack_shouldSetHeadAndTailEqualWhenListIsEmpty)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertBack(1, 2);
	ASSERT_TRUE(nullptr != intDLL.getHead());
	ASSERT_TRUE(nullptr != intDLL.getTail());
	ASSERT_TRUE(helper::isDLLEqual(std::vector<std::pair<unsigned, int>>{std::make_pair(1,2)}, intDLL.getHead()));
}

TEST(TestCircularDoublyLinkedList, insertBack_shouldInsertInCorrectOrder)
{
	CircularDoublyLinkedList<int> intDLL;
	for(auto i = 0u; i < 10; ++i)
	{
		intDLL.insertBack(i, i*2);
	}
	ASSERT_TRUE(helper::isDLLEqual(helper::createExpectedMessageDLL(), intDLL.getHead()));
}

TEST(TestCircularDoublyLinkedList, getNodeWithKey_shouldReturnNullptrWhenListIsEmpty)
{
	CircularDoublyLinkedList<int> intDLL;
	ASSERT_TRUE((nullptr == intDLL.getNodeWithKey(1)));
}

TEST(TestCircularDoublyLinkedList, getNodeWithKey_shouldReturnCorrectNodeWhenListHasOneElem)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertFront(1,2);
	ASSERT_EQ(intDLL.getHead(), intDLL.getNodeWithKey(1));
}

TEST(TestCircularDoublyLinkedList, getNodeWithKey_shouldReturnCorrectNodeWhenListHasTwoElem)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertFront(1,2);
	intDLL.insertBack(2,4);
	ASSERT_EQ(intDLL.getHead(), intDLL.getNodeWithKey(1));
	ASSERT_EQ(intDLL.getTail(), intDLL.getNodeWithKey(2));
}

TEST(TestCircularDoublyLinkedList, insertAfterKey_shouldDoNothingWhenKeyToSearchIsNotInList)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertAfterKey(1,1,1);
	ASSERT_TRUE((nullptr == intDLL.getNodeWithKey(1)));
}

TEST(TestCircularDoublyLinkedList, insertAfterKey_shouldInsertBackWhenThereIsOnlyOneElementInList)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertFront(1,2);
	intDLL.insertAfterKey(1,69,69);
	ASSERT_TRUE(helper::isDLLEqual(std::vector<std::pair<unsigned, int>>{std::make_pair(1,2), std::make_pair(69,69)}, intDLL.getHead()));
}

TEST(TestCircularDoublyLinkedList, insertAfterKey_shouldInsertInCorrectPositionWhenKeyToSearchIsNeitherHeadOrTail)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertBack(0,0);
	intDLL.insertBack(1,5);
	intDLL.insertBack(2,10);
	intDLL.insertAfterKey(1,69,69);
	auto EXPECTED = std::vector<std::pair<unsigned, int>>{std::make_pair(0,0), std::make_pair(1,5), std::make_pair(69,69),
		std::make_pair(2,10)};
	ASSERT_TRUE(helper::isDLLEqual(EXPECTED, intDLL.getHead()));
}

TEST(TestCircularDoublyLinkedList, insertBeforeKey_shouldDoNothingWhenKeyToSearchIsNotInList)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertBeforeKey(1,1,1);
	ASSERT_TRUE((nullptr == intDLL.getNodeWithKey(1)));
}

TEST(TestCircularDoublyLinkedList, insertBeforeKey_shouldInsertFrontWhenThereIsOnlyOneElementInList)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertFront(1,2);
	intDLL.insertBeforeKey(1,69,69);
	ASSERT_TRUE(helper::isDLLEqual(std::vector<std::pair<unsigned, int>>{std::make_pair(69,69), std::make_pair(1,2)}, intDLL.getHead()));
}

TEST(TestCircularDoublyLinkedList, insertBeforeKey_shouldInsertInCorrectPositionWhenKeyToSearchIsNeitherHeadOrTail)
{
	CircularDoublyLinkedList<int> intDLL;
	intDLL.insertBack(0,0);
	intDLL.insertBack(1,5);
	intDLL.insertBack(2,10);
	intDLL.insertBeforeKey(1,69,69);
	auto EXPECTED = std::vector<std::pair<unsigned, int>>{std::make_pair(0,0), std::make_pair(69,69), std::make_pair(1,5),
		std::make_pair(2,10)};
	ASSERT_TRUE(helper::isDLLEqual(EXPECTED, intDLL.getHead()));
}
