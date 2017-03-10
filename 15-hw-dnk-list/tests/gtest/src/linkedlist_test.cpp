////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::LinkedList<T> class
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      23.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>


#include "linked_list.h"


TEST(StackArray, simplest)
{
    using namespace xi;

    LinkedList<int> sa;
}


TEST(StackArray, DefConstructor)
{
    using namespace xi;

    LinkedList<int> sa;
    EXPECT_NE(sa.getPreHead(), nullptr);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.getEndNode(), sa.getPreHead());
}


TEST(StackArray, EndNodeEmpty)
{
    using namespace xi;

    LinkedList<int> sa;
    EXPECT_NE(sa.getPreHead(), nullptr);
    EXPECT_EQ(sa.size(), 0);
    EXPECT_EQ(sa.getEndNode(), sa.getPreHead());
}

TEST(StackArray, EndNodeOne)
{
    using namespace xi;

    int data[] = {0, 1, 2, 3};
    LinkedList<int> sa;
    sa.addElementToEnd(data[0]);
    EXPECT_EQ(sa.size(), 1);
    EXPECT_EQ(sa.getEndNode(), sa.getPreHead()->next);
}


TEST(StackArray, IndexOper1)
{
    using namespace xi;
    int data[] = {0, 1, 2, 3};
    LinkedList<int> sa;
    sa.addElementToEnd(data[0]);
    sa.addElementToEnd(data[1]);
    sa.addElementToEnd(data[2]);
    sa.addElementToEnd(data[3]);
    EXPECT_EQ(sa.size(), 4);
    EXPECT_EQ(sa[0], 0);
    EXPECT_EQ(sa[1], 1);
    EXPECT_EQ(sa[2], 2);
    EXPECT_EQ(sa[3], 3);
    EXPECT_EQ(sa[sa.size()-1], 3);
    EXPECT_EQ(sa.getEndNode()->value, 3);

    // out of range:
    EXPECT_THROW(sa[6], std::out_of_range);
    EXPECT_THROW(sa[4], std::out_of_range);
    EXPECT_THROW(sa[sa.size()], std::out_of_range);
}


TEST(StackArray, CopyConstructor)
{
    using namespace xi;

    int data[] = {0, 1, 2, 3};
    LinkedList<int> sa;
    sa.addElementToEnd(data[0]);
    sa.addElementToEnd(data[1]);
    sa.addElementToEnd(data[2]);
    sa.addElementToEnd(data[3]);

    LinkedList<int> sb{sa};
    sb.addElementToEnd(data[0]);

    ASSERT_NE(sb.size(), sa.size());
    ASSERT_NE(sa.getPreHead(), sb.getPreHead());
}

