#include <gtest/gtest.h>

#include <MaVector.hpp>

TEST(MaVectorTest, constructorWithSizeAndVal_shouldInitializeCorrectValues)
{
	MaVector<int> maVec(10, 2);
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(10), maVec.size());
	for(MaVector<int>::iterator it = maVec.begin(); it != maVec.end(); ++it)
	{
		ASSERT_EQ(2, *it);
	}
}

TEST(MaVectorTest, defaultConstructor_shouldHaveCorrectSize)
{
	MaVector<int> maVec;
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(0), maVec.size());
}

TEST(MaVectorTest, initializerListConstructor_randomTests)
{
	MaVector<int> maVec{1,2,3,4,5};
	ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(5), maVec.size());
	MaVector<int> maVec2{};
	ASSERT_EQ(static_cast<unsigned>(20), maVec2.max_size());
	ASSERT_EQ(static_cast<unsigned>(0), maVec2.size());
}

TEST(MaVectorTest, pushBack_MultipleTests)
{
	MaVector<int> maVec;
	maVec.push_back(12);
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(1), maVec.size());
	ASSERT_EQ(12, *maVec.begin());
	MaVector<int> maVec2(10, 1);
	ASSERT_EQ(static_cast<unsigned>(20), maVec2.max_size());
	ASSERT_EQ(static_cast<unsigned>(10), maVec2.size());
	maVec2.push_back(69);
	ASSERT_EQ(static_cast<unsigned>(20), maVec2.max_size());
	ASSERT_EQ(static_cast<unsigned>(11), maVec2.size());
	for(auto it = maVec2.begin(); it != maVec2.end(); ++it)
	{
		if(it != maVec2.end()-1)
		{
			ASSERT_EQ(1, *it);
		}
		else
		{
			ASSERT_EQ(69, *it);
		}
	}
}

TEST(MaVectorTest, popBack_MultipleTests)
{
	MaVector<int> maVec(2, 1);
	ASSERT_EQ(static_cast<unsigned>(4), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(2), maVec.size());
	maVec.pop_back();
	ASSERT_EQ(static_cast<unsigned>(1), maVec.size());
	MaVector<int> maVec2;
	ASSERT_EQ(static_cast<unsigned>(20), maVec2.max_size());
	ASSERT_EQ(static_cast<unsigned>(0), maVec2.size());
	maVec2.pop_back();
	ASSERT_EQ(static_cast<unsigned>(20), maVec2.max_size());
	ASSERT_EQ(static_cast<unsigned>(0), maVec2.size());
}

TEST(MaVectorTest, resize_shouldReturnCorrectSizeAndSetValues)
{
	MaVector<int> maVec(10, 1);
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(10), maVec.size());
	maVec.resize(11, 69);
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(11), maVec.size());
	for(auto it = maVec.begin(); it != maVec.end(); ++it)
	{
		if(it != maVec.end()-1)
		{
			ASSERT_EQ(1, *it);
		}
		else
		{
			ASSERT_EQ(69, *it);
		}
	}
	maVec.resize(5, 69);
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(5), maVec.size());
	for(auto it = maVec.begin(); it != maVec.end(); ++it)
	{
		ASSERT_EQ(1, *it);
	}
	maVec.resize(19, 69);
	maVec.resize(19, 69);
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(19), maVec.size());
	auto it = maVec.begin();
	for(auto i = 0u; i < 19; ++i)
	{
		if(i < 5)
		{
			ASSERT_EQ(1, *(it + i));
		}
		else
		{
			ASSERT_EQ(69, *(it + i));
		}
	}
	maVec.resize(50, 69);
	ASSERT_EQ(static_cast<unsigned>(80), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(50), maVec.size());
	it = maVec.begin();
	for(auto i = 0u; i < 50; ++i)
	{
		if(i < 5)
		{
			ASSERT_EQ(1, *(it + i));
		}
		else
		{
			ASSERT_EQ(69, *(it + i));
		}
	}
}

TEST(MaVectorTest, assignWithFirstAndLastIteratorParameter_MultipleTests)
{
	/*Input:
	 * vector to call assign -> maxSize 20, val 10, size 10
	 * vector to copy from -> maxSize 100, val 50, size 50
	 * */
	{
		//TEST 1: call assign maxSize > newCurrsize
		MaVector<int> maVec1(10, 10);
		MaVector<int> maVec2(50, 50);
		maVec1.assign(maVec2.begin(), maVec2.begin()+2);
		ASSERT_EQ(static_cast<unsigned>(20), maVec1.max_size());
		ASSERT_EQ(static_cast<unsigned>(12), maVec1.size());
		auto it = maVec1.begin();
		for(auto i = 0u; i < maVec1.size(); ++i)
		{
			if(i < 10)
			{
				ASSERT_EQ(10, *(it + i));
			}
			else
			{
				ASSERT_EQ(50, *(it + i));
			}
		}
	}

	{
		//TEST 2: call assign maxSize < newCurrSize
		MaVector<int> maVec1(10, 10);
		MaVector<int> maVec2(50, 50);
		maVec1.assign(maVec2.begin(), maVec2.end());
		ASSERT_EQ(static_cast<unsigned>(80), maVec1.max_size());
		ASSERT_EQ(static_cast<unsigned>(60), maVec1.size());
		auto it = maVec1.begin();
		for(auto i = 0u; i < maVec1.size(); ++i)
		{
			if(i < 10)
			{
				ASSERT_EQ(10, *(it + i));
			}
			else
			{
				ASSERT_EQ(50, *(it + i));
			}
		}
	}
}

TEST(MaVectorTest, assignWithSizeAndValueParameter_shouldReturnCorrectValueAndSizeMaxSize)
{
	MaVector<int> maVec(10, 50);
	maVec.assign(50, 50);
	ASSERT_EQ(static_cast<unsigned>(80), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(60), maVec.size());
}

TEST(MaVectorTest, assign_initializerListShouldReturnCorrectValueSizeMaxSize)
{
	MaVector<int> maVec(10, 50);
	ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(10), maVec.size());
	maVec.assign({50,50,50,50,50,50,50,50,50,50,50,50,50,50,50});
	ASSERT_EQ(static_cast<unsigned>(40), maVec.max_size());
	ASSERT_EQ(static_cast<unsigned>(25), maVec.size());
}

TEST(MaVectorTest, clear_multipleTests)
{
	{
		//Test 1: clear on empty vector
		MaVector<int> maVec;
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(0), maVec.size());
		maVec.clear();
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(0), maVec.size());
	}

	{
		//Test 2: clear in non empty vector
		MaVector<int> maVec(10, 50);
		maVec.clear();
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(0), maVec.size());
	}
}

TEST(MaVectorTest, insert_oneRValue)
{
	{
		//TEST 1: perform insert when currSize < maxSize
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.insert(maVec.begin()+1, 69);
		ASSERT_EQ(69, *it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(6), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i == 1)
			{
				ASSERT_EQ(69, *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(static_cast<int>(1), *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i), *(maVec.begin()+i));
			}
		}
	}
	{
		//TEST 2: perform insert when currSize >= maxSize
		MaVector<int> maVec{1,2,3,4,5};
		maVec.push_back(50);
		maVec.push_back(50);
		maVec.push_back(50);
		maVec.push_back(50);
		maVec.push_back(50);
		auto it = maVec.insert(maVec.begin()+1, 69);
		ASSERT_EQ(69, *it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(11), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i == 1)
			{
				ASSERT_EQ(69, *(maVec.begin()+i));

			}
			else if(i == 0)
			{
				ASSERT_EQ(static_cast<int>(i+1), *(maVec.begin()+i));
			}
			else if(i > 1 && i < 6)
			{
				ASSERT_EQ(static_cast<int>(i), *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(50, *(maVec.begin()+i));
			}
		}
	}
}

TEST(MaVectorTest, insert_oneLValue)
{
	int lValueInput = 69;
	{
		//TEST 1: perform insert when currSize < maxSize
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.insert(maVec.begin()+1, 69);
		ASSERT_EQ(lValueInput, *it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(6), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i == 1)
			{
				ASSERT_EQ(69, *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(static_cast<int>(1), *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i), *(maVec.begin()+i));
			}
		}
	}
	{
		//TEST 2: perform insert when currSize >= maxSize
		MaVector<int> maVec{1,2,3,4,5};
		maVec.push_back(50);
		maVec.push_back(50);
		maVec.push_back(50);
		maVec.push_back(50);
		maVec.push_back(50);
		auto it = maVec.insert(maVec.begin()+1, 69);
		ASSERT_EQ(lValueInput, *it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(11), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i == 1)
			{
				ASSERT_EQ(69, *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(static_cast<int>(i+1), *(maVec.begin()+i));
			}
			else if(i > 1 && i < 6)
			{
				ASSERT_EQ(static_cast<int>(i), *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(50, *(maVec.begin()+i));
			}
		}
	}
}

TEST(MaVectorTest, insert_initializerListInput)
{
	{
		//TEST 1: insert in empty vector
		MaVector<int> maVec{};
		auto it = maVec.insert(maVec.begin(), {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21});
		ASSERT_EQ(0, *it);
		ASSERT_EQ(static_cast<unsigned>(40), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(22), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			ASSERT_EQ(static_cast<int>(i), *(maVec.begin()+i));
		}
	}
	{
		//TEST 2: insert in vector where currSize < maxSize
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.insert(maVec.begin()+1, {10,20,30});
		ASSERT_EQ(10, *it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(8), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i > 0 && i < 4)
			{
				ASSERT_EQ(static_cast<int>(i*10), *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(1, *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i-2), *(maVec.begin()+i));
			}
		}
	}

	{
		//TEST 3: insert in vector when currSize >= maxSize
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.insert(maVec.begin()+1, {10,20,30,40,50,60});
		ASSERT_EQ(10, *it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(11), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i > 0 && i < 7)
			{
				ASSERT_EQ(static_cast<int>(i*10), *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(1, *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i-5), *(maVec.begin()+i));
			}
		}
	}

}

TEST(MaVectorTest, insert_rangeIteratorFirstUntilLast)
{
	{
		//TEST 1: insert in empty vector
		MaVector<int> maVec{};
		MaVector<int> maVec2{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
		auto it = maVec.insert(maVec.begin(), maVec2.begin(), maVec2.end());
		ASSERT_EQ(0, *it);
		ASSERT_EQ(static_cast<unsigned>(40), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(22), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			ASSERT_EQ(static_cast<int>(i), *(maVec.begin()+i));
		}
	}
	{
		//TEST 2: insert in vector where currSize < maxSize
		MaVector<int> maVec{1,2,3,4,5};
		MaVector<int> maVec2{10,20,30};
		auto it = maVec.insert(maVec.begin()+1, maVec2.begin(), maVec2.end());
		ASSERT_EQ(10, *it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(8), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i > 0 && i < 4)
			{
				ASSERT_EQ(static_cast<int>(i*10), *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(1, *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i-2), *(maVec.begin()+i));
			}
		}
	}

	{
		//TEST 3: insert in vector when currSize >= maxSize
		MaVector<int> maVec{1,2,3,4,5};
		MaVector<int> maVec2{10,20,30,40,50,60};
		auto it = maVec.insert(maVec.begin()+1, maVec2.begin(), maVec2.end());
		ASSERT_EQ(10, *it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(11), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i > 0 && i < 7)
			{
				ASSERT_EQ(static_cast<int>(i*10), *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(1, *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i-5), *(maVec.begin()+i));
			}
		}
	}

}

TEST(MaVectorTest, insert_valWithSizeN)
{
	{
		//TEST 1: insert in empty vector
		MaVector<int> maVec{};
		auto it = maVec.insert(maVec.begin(), 21, 69);
		ASSERT_EQ(69, *it);
		ASSERT_EQ(static_cast<unsigned>(40), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(21), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			ASSERT_EQ(69, *(maVec.begin()+i));
		}
	}
	{
		//TEST 2: insert in vector where currSize < maxSize
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.insert(maVec.begin()+1, 3, 69);
		ASSERT_EQ(69, *it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(8), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i > 0 && i < 4)
			{
				ASSERT_EQ(69, *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(1, *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i-2), *(maVec.begin()+i));
			}
		}
	}

	{
		//TEST 3: insert in vector when currSize >= maxSize
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.insert(maVec.begin()+1, 6, 69);
		ASSERT_EQ(69, *it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(11), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
		{
			if(i > 0 && i < 7)
			{
				ASSERT_EQ(69, *(maVec.begin()+i));
			}
			else if(i == 0)
			{
				ASSERT_EQ(1, *(maVec.begin()+i));
			}
			else
			{
				ASSERT_EQ(static_cast<int>(i-5), *(maVec.begin()+i));
			}
		}
	}

}

TEST(MaVectorTest, erase_onePosIterator)
{
	{
		//TEST 1: Erase at end
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.erase(maVec.end()-1);
		ASSERT_EQ(maVec.end(), it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(4), maVec.size());
	}
	{
		//TEST 2: Erase at middle
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.erase(maVec.end()-3);
		ASSERT_EQ(4, *it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(4), maVec.size());
		ASSERT_EQ(1, *(maVec.begin()));
		ASSERT_EQ(2, *(maVec.begin()+1));
		ASSERT_EQ(4, *(maVec.begin()+2));
		ASSERT_EQ(5, *(maVec.begin()+3));
	}
	{
		//TEST 3: Erase at front
		MaVector<int> maVec{1,2,3,4,5};
		auto it = maVec.erase(maVec.begin());
		ASSERT_EQ(2, *it);
		ASSERT_EQ(static_cast<unsigned>(10), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(4), maVec.size());
		ASSERT_EQ(2, *(maVec.begin()));
		ASSERT_EQ(3, *(maVec.begin()+1));
		ASSERT_EQ(4, *(maVec.begin()+2));
		ASSERT_EQ(5, *(maVec.begin()+3));
	}
}

TEST(MaVectorTest, erase_rangeIterator)
{
	{
		//TEST 1: Erase first upto end()
		MaVector<int> maVec{1,2,3,4,5,6,7,8,9,10};
		auto it = maVec.erase(maVec.end()-5, maVec.end());
		ASSERT_EQ(maVec.end(), it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(5), maVec.size());
		for(auto i = 0u; i < maVec.size(); ++i)
			ASSERT_EQ(static_cast<int>(i+1), *((maVec.data())+i));
	}
	{
		//TEST 2: Erase at middle
		MaVector<int> maVec{1,2,3,4,5,6,7,8,9,10};
		auto it = maVec.erase(maVec.end()-8, maVec.end()-2);
		ASSERT_EQ(9, *it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(4), maVec.size());
		for(auto i = 0u; i < 2; ++i)
			ASSERT_EQ(static_cast<int>(i+1), *((maVec.data())+i));
		for(auto i = 2u; i < 4; ++i)
			ASSERT_EQ(static_cast<int>(i+7), *((maVec.data())+i));
	}
	{
		//TEST 3: Erase at front upto middle
		MaVector<int> maVec{1,2,3,4,5,6,7,8,9,10};
		auto it = maVec.erase(maVec.begin(), maVec.begin()+5);
		ASSERT_EQ(6, *it);
		ASSERT_EQ(static_cast<unsigned>(20), maVec.max_size());
		ASSERT_EQ(static_cast<unsigned>(5), maVec.size());
		for(auto i = 0u; i < 5; ++i)
			ASSERT_EQ(static_cast<int>(i+6), *((maVec.data())+i));
	}
}
