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

#include "subject.h"


// TODO: укажите здесь абсолютный путь к файлу с описанием предметов
static const char* TEST_FNAME = "/home/artem/Desktop/Uni/algo-structs/14-hw-safe-array/tests/gtest/src/subjects.txt";

// число описаний курсов в файле
static const int SUBS_NUM = 10;




// Вспомогательный метод, загружающий список предметов из текстового файла, имя
// которого передается параметром
// Список загружается в передаваемый по ссылке объект ar
// Использование передачи объектов по значению в данном случае является дорогим и нерациональным
void loadSubjects(const char* fn, xi::SafeArray<xi::Subject>& subjs)
{
    using namespace std;

    // пытаемся открыть файл для чтения
    ifstream inf(fn);
    bool fileNotOpen = !inf;
    ASSERT_FALSE(fileNotOpen);

    // пытаемся вычитать текстовый файл строку за строкой
    try
    {
        for (int i = 0; i < SUBS_NUM; i++)
        {
            inf >> subjs[i];
            cerr << subjs[i];
        }
    }
    catch (out_of_range e)
    {
        cerr << "Error reading file" << fn << endl;
    }
    
    inf.close();
}

TEST(Subject, simplest)
{
    using namespace xi;

    Subject s;
}


TEST(Subject, OpenDemoFile)
{
    using namespace xi;

    xi::SafeArray<xi::Subject> subjs(SUBS_NUM);
    loadSubjects(TEST_FNAME, subjs);
}


TEST(Subject, DemoFile1)
{
    using namespace xi;

    xi::SafeArray<xi::Subject> subjs(SUBS_NUM);
    loadSubjects(TEST_FNAME, subjs);

    EXPECT_EQ(subjs[1].name, "SSD2");
    EXPECT_EQ(subjs[1].title, "Introduction to Computer Systems");
    
    // след. две строки эквивалентны
    EXPECT_EQ(subjs[1].description.getCapacity(), 10);
    EXPECT_EQ(subjs[1].description.getCapacity(), 10);
}
