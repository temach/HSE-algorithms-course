////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Main module for xi Point project
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      14.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// The module provides only a simple "smoke" test if the point class compiles well.
///
////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include "xipoint.h"



int main(int argc, char** argv)
{
    using namespace xi;

    std::cout << "Hello, world!";

    Point p;
    Point p1{1, 0};
    PointArray ar;

    ar.append(Point{2, 0});
    ar.append(Point{4, 0});
    p1.setX(1);
    ar.insert(p1, 0);
    p1.setX(3);
    ar.insert(p1, 2);
    p1.setX(100);
    ar.insert(p1, ar.getSize());
    p1.setX(1000);
    ar.insert(p1, ar.getSize());

    PointArray a;

    //std::getchar();

}
