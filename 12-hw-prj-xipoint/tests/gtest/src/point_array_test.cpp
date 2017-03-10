////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit test for xi::PointArray class
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

TEST(XiPointArray, simplest)
{
    using namespace xi;

    PointArray ar1;    
}

// !should not be given to students
TEST(XiPointArray, properInit)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 0);
}



TEST(XiPointArray, initByArray)
{

    using namespace xi;

    Point testAr[] = { Point(1, 1), Point(2, 2), Point(3, 3) };
    PointArray::Uint testArSize = sizeof(testAr) / sizeof(testAr[0]);

    PointArray ar1(testAr, testArSize);
    EXPECT_NE(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), testArSize);

    EXPECT_EQ(ar1.get(0)->getX(), 1);
    EXPECT_EQ(ar1.get(1)->getX(), 2);
    
    // .:xi cut:.
}

// .:xi cut:.


// !should not be given to students
TEST(XiPointArray, clear1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 0);

    Point p1(10, 15);
    ar1.append(p1);

    EXPECT_NE(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 1);
    
    ar1.clear();

    // .:xi cut:.
}

// !should not be given to students
TEST(XiPointArray, remove1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 0);
    
    ar1.append(Point(0, 0));
    ar1.append(Point(1, 1));
    ar1.append(Point(2, 2));
    ar1.append(Point(3, 3));
    ar1.append(Point(4, 4));
    

    EXPECT_NE(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 5);

    // trying to remove a non existing element
    ar1.remove(5);
    EXPECT_NE(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 5);

    // .:xi cut:.
}

TEST(XiPointArray, get1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 0);

    EXPECT_EQ(ar1.get(0), nullptr);
    EXPECT_EQ(ar1.get(1), nullptr);

    // .:xi cut:.
}


TEST(XiPointArray, insert1)
{
    using namespace xi;

    PointArray ar1;
    EXPECT_EQ(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 0);

    Point p1(10, 15);
    ar1.insert(p1, 0);

    EXPECT_NE(ar1.getRawPtr(), nullptr);
    EXPECT_EQ(ar1.getSize(), 1);
}
