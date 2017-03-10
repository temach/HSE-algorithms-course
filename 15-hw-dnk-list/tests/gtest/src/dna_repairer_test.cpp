////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::Subject class
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

#include <fstream>

#include "dna_repairer.h"


static const char* TEST_FNAMES[] = {
    "test.in"
    , "test2.in"
    , "test3.in"
    , "test5.in"
};


TEST(Subject, DemoFile1)
{
    using namespace xi;

    // xi::SafeArray<xi::Subject> subjs(SUBS_NUM);
    // loadSubjects(TEST_FNAME, subjs);

    // EXPECT_EQ(subjs[1].name, "SSD2");
    // EXPECT_EQ(subjs[1].title, "Introduction to Computer Systems");
    // 
    // // след. две строки эквивалентны
    // EXPECT_EQ(subjs[1].description.getCapacity(), 10);
    // EXPECT_EQ(subjs[1].description.getCapacity(), 10);
}
