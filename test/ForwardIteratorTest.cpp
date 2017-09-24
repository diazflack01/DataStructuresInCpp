#include <gtest/gtest.h>

#include <ForwardIterator.hpp>

int intArrayTestInput[] = {1, 2, 3, 4, 5};

TEST(ForwardIteratorTest, constructorWhenDefaultInitialized)
{
	ForwardIterator<int> fItr;
	ASSERT_TRUE((nullptr == fItr.getConstPtr()));
	ASSERT_TRUE((nullptr == fItr.getPtr()));
}

TEST(ForwardIteratorTest, constructorWhenPassedWithTElemShouldReturnT)
{
	ForwardIterator<int> fItr(intArrayTestInput);
	ASSERT_TRUE((intArrayTestInput == fItr.getConstPtr()));
	ASSERT_TRUE((intArrayTestInput == fItr.getPtr()));
	ASSERT_EQ(intArrayTestInput[0], *fItr);
}

TEST(ForwardIteratorTest, constructorWhenPassedWithForwardIteratorObjectShouldHaveSameValueAsPassedObject)
{
	ForwardIterator<int> fItr1(intArrayTestInput);
	ForwardIterator<int> fItr2(fItr1);
	ASSERT_TRUE((fItr2.getConstPtr() == fItr1.getConstPtr()));
	ASSERT_TRUE((fItr2.getPtr() == fItr1.getPtr()));
	ASSERT_EQ(*fItr2, *fItr1);
}

TEST(ForwardIteratorTest, copyAssignmentShouldHaveSameValueAsPassedObject)
{
	ForwardIterator<int> fItr1(intArrayTestInput);
	ForwardIterator<int> fItr2 = fItr1;
	ASSERT_TRUE((fItr2.getConstPtr() == fItr1.getConstPtr()));
	ASSERT_TRUE((fItr2.getPtr() == fItr1.getPtr()));
	ASSERT_EQ(*fItr2, *fItr1);
}


TEST(ForwardIteratorTest, equaltoOperatorShouldReturnTrueIfSameIterator)
{
	ForwardIterator<int> fItr1(intArrayTestInput);
	ForwardIterator<int> fItr2 = fItr1;
	ASSERT_TRUE((fItr2 == fItr1));
}

TEST(ForwardIteratorTest, equaltoOperatorShouldReturnFalseIfNotSameIterator)
{
	ForwardIterator<int> fItr1(intArrayTestInput);
	ForwardIterator<int> fItr2 = fItr1;
	++fItr2;
	ASSERT_FALSE((fItr2 == fItr1));
}

TEST(ForwardIteratorTest, notqualitoOperatorShouldReturnTrueIfNotSameIterator)
{
	ForwardIterator<int> fItr1(intArrayTestInput);
	ForwardIterator<int> fItr2 = fItr1;
	++fItr2;
	ASSERT_TRUE((fItr2 == fItr1));
}

TEST(ForwardIteratorTest, notequaltoOperatorShouldReturnFalseIfSameIterator)
{
	ForwardIterator<int> fItr1(intArrayTestInput);
	ForwardIterator<int> fItr2 = fItr1;
	ASSERT_FALSE((fItr2 != fItr1));
}

TEST(ForwardIteratorTest, dereferenceOperatorShouldReturnCorrectValue)
{
	const ForwardIterator<int> fItr1(intArrayTestInput);
	ASSERT_EQ(intArrayTestInput[0], *fItr1);
	ForwardIterator<int> fItr2(&intArrayTestInput[4]);
	ASSERT_EQ(intArrayTestInput[4], *fItr2);
}

TEST(ForwardIteratorTest, incrementOperatorShouldReturnNextElem)
{
	ForwardIterator<int> fItr1(intArrayTestInput);
	++fItr1;
	ASSERT_EQ(intArrayTestInput[1], *fItr1);
}
