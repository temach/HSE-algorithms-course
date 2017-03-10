////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::Point class
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      14.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
/// Note the issue about including point modules here (ask the trainer about).
/// 
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>


#include "xipoint.h"

TEST(XiPoint, simplest)
{
    using namespace xi;

    Point p1;
    Point p2(1, 1);
}


TEST(XiPoint, constructorDef)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(p1.getX(), 0);
    EXPECT_EQ(p1.getY(), 0);

    // .:xi cut:.
}

TEST(XiPoint, set1)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(p1.getX(), 0);
    EXPECT_EQ(p1.getY(), 0);

    p1.setX(42);
    p1.setY(13);
    EXPECT_EQ(p1.getX(), 42);
    EXPECT_EQ(p1.getY(), 13);

}


TEST(XiPoint, shift1)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(p1.getX(), 0);
    EXPECT_EQ(p1.getY(), 0);

    p1.shift(15);
    EXPECT_EQ(p1.getX(), 15);
    EXPECT_EQ(p1.getY(), 15);
}

// .:xi cut:.

TEST(XiPoint, shift4)
{
    using namespace xi;

    Point p1;
    EXPECT_EQ(p1.getX(), 0);
    EXPECT_EQ(p1.getY(), 0);

    Point p2(5, 10);
    EXPECT_EQ(p2.getX(), 5);
    EXPECT_EQ(p2.getY(), 10);
    
    // .:xi cut:.
}

