#include <gtest/gtest.h>

#include <BidirectionalIterator.hpp>

namespace {
int intArrayTestInput[] = {1, 2, 3, 4, 5};
}

TEST(BiderectionalIteratorTest, constructor_shouldReturnNullptrWhenDefaultInitialized)
{
	BidirectionalIterator<int> biItr;
	ASSERT_TRUE((nullptr == biItr.getPtr()));
}

TEST(BiderectionalIteratorTest, constructor_shouldReturnSamePointerWhenPassedWithPointerObject)
{
	BidirectionalIterator<int> biItr(intArrayTestInput);
	ASSERT_EQ(1, *biItr);
}

TEST(BiderectionalIteratorTest, copyAssigment_shouldReturnSamePointee)
{
	BidirectionalIterator<int> biItr = intArrayTestInput;
	ASSERT_EQ(1, *biItr);
}

TEST(BiderectionalIteratorTest, equalTo_shouldReturnTrueWhenSameIterator)
{
	BidirectionalIterator<int> biItr1(intArrayTestInput);
	BidirectionalIterator<int> biItr2(intArrayTestInput);
	ASSERT_TRUE(biItr1 == biItr2);
}

TEST(BiderectionalIteratorTest, equalTo_shouldReturnFalseWhenNotSameIterator)
{
	BidirectionalIterator<int> biItr1(intArrayTestInput);
	BidirectionalIterator<int> biItr2(&intArrayTestInput[1]);
	ASSERT_FALSE(biItr1 == biItr2);
}

TEST(BiderectionalIteratorTest, notEqualTo_shouldReturnFalseWhenSameIterator)
{
	BidirectionalIterator<int> biItr1(intArrayTestInput);
	BidirectionalIterator<int> biItr2(intArrayTestInput);
	ASSERT_FALSE(biItr1 != biItr2);
}

TEST(BiderectionalIteratorTest, notEqualTo_shouldReturnTrueWhenNotSameIterator)
{
	BidirectionalIterator<int> biItr1(intArrayTestInput);
	BidirectionalIterator<int> biItr2(&intArrayTestInput[1]);
	ASSERT_TRUE(biItr1 != biItr2);
}

TEST(BiderectionalIteratorTest, dereferenceOperator_shouldReturnReferenceType)
{
	int localIntArrayTestInput[] = {1, 2, 3, 4, 5};
	BidirectionalIterator<int> biItr1(localIntArrayTestInput);
	int& e = *biItr1;
	e = 69;
	ASSERT_EQ(69, localIntArrayTestInput[0]);
}

TEST(BiderectionalIteratorTest, dereferenceOperator_shouldReturnConstReferenceType)
{
	int localIntArrayTestInput[] = {1, 2, 3, 4, 5};
	BidirectionalIterator<int> biItr1(localIntArrayTestInput);
	const int& e = *biItr1;
	ASSERT_EQ(e, localIntArrayTestInput[0]);
}

TEST(BiderectionalIteratorTest, incrementOperator_shouldIncrementToNextElem)
{
	BidirectionalIterator<int> biItr1(intArrayTestInput);
	BidirectionalIterator<int> biItr2(&intArrayTestInput[1]);
	ASSERT_EQ(biItr2, ++biItr1);
}

TEST(BiderectionalIteratorTest, decrementOperator_shouldDecrementToNextElem)
{
	BidirectionalIterator<int> biItr1(&intArrayTestInput[1]);
	BidirectionalIterator<int> biItr2(&intArrayTestInput[1]);
	ASSERT_TRUE((biItr2 != --biItr1));
}
